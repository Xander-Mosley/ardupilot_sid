#!/usr/bin/env python3
"""Live DDS safeguards/output assertions against an already airborne SITL instance."""
import argparse
import json
import math
import time
import rclpy
from rclpy.node import Node
from ardupilot_msgs.msg import ControlSurfaceExcitation, ControlSurfaceOutput
from builtin_interfaces.msg import Time
from ros2_sid.surface_mission import QOS
from ros2_sid.surface_analysis import expected_pwm
from pymavlink import mavutil

class Probe(Node):
    def __init__(self):
        super().__init__('surface_probe');self.clock=None;self.frame=None;self.seq=100000
        self.pub=self.create_publisher(ControlSurfaceExcitation,'/ap/sid/control_surface',QOS)
        self.create_subscription(Time,'/ap/time',self.time_cb,QOS)
        self.create_subscription(ControlSurfaceOutput,'/ap/sid/output',self.out_cb,QOS)
        self.samples=[]
    def time_cb(self,m):self.clock=(m.sec+m.nanosec*1e-9,time.monotonic())
    def out_cb(self,m):self.frame=m;self.samples.append(m)
    def spin(self,duration):
        end=time.monotonic()+duration
        while time.monotonic()<end:rclpy.spin_once(self,timeout_sec=.01)
    def send(self,enabled=True,values=(.1,.02,-.02),stale=False,duplicate=False):
        m=ControlSurfaceExcitation();m.sequence_id=self.seq
        if not duplicate:self.seq=(self.seq+1)&0xffffffff
        now=self.clock[0]+time.monotonic()-self.clock[1]-(1 if stale else 0)
        m.stamp.sec=int(now);m.stamp.nanosec=int((now-int(now))*1e9)
        m.enable=enabled;m.roll,m.pitch,m.yaw=values;self.pub.publish(m)
    def stream(self,duration,**kw):
        end=time.monotonic()+duration
        while time.monotonic()<end:self.send(**kw);self.spin(.02)
    def handshake(self):
        self.stream(.3,enabled=False,values=(0.,0.,0.));assert self.frame.state==1, self.frame
    def zero(self):
        assert all(d==0 for d in self.frame.delta),list(self.frame.delta)
    def validate(self):
        assert self.frame.state==2,self.frame
        nonzero=False
        for i in range(self.frame.count):
            if self.frame.function[i] not in (4,19,21,24,25,77,78,79,80):continue
            m=self.frame
            roll,pitch,yaw=map(float,m.applied)
            def mixed(first, second):
                if m.mixing_offset<0:second*=1-m.mixing_offset/100
                elif m.mixing_offset>0:first*=1+m.mixing_offset/100
                return ((second-first)*m.mixing_gain,(second+first)*m.mixing_gain)
            el,er=mixed(roll,pitch);vr,vl=mixed(yaw,pitch)
            logical={4:roll,19:pitch,21:yaw,24:roll,25:roll,77:el,78:er,79:vl,80:vr}
            # The sample parameters cap each physical contribution at 0.20.
            wanted=max(-.2,min(.2,logical[int(m.function[i])]))
            assert abs(float(m.excitation[i])-wanted)<1e-6,(i,m.excitation[i],wanted)
            expected=expected_pwm(m.excitation[i],m.baseline[i],m.minimum[i],m.trim[i],m.maximum[i],m.reversed[i])
            assert abs(int(m.pwm[i])-expected)<=1,(i,m.pwm[i],expected)
            nonzero |= m.delta[i]!=0
        assert nonzero,'No physical PWM perturbation'

def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--mavlink",default="tcp:127.0.0.1:5782")
    args=parser.parse_args()
    rclpy.init();p=Probe();results={}
    try:
        p.spin(3);assert p.clock and p.frame,'No DDS clock/output'
        p.handshake();p.stream(.5);p.validate();results['simultaneous_calibrated_pwm']=True
        p.stream(.5,duplicate=True);p.spin(.25);assert p.frame.state==3;p.zero();results['duplicate_timeout']=True
        p.handshake();p.stream(.2);p.stream(.6,stale=True);p.zero();results['stale_timestamp']=True
        p.handshake();p.stream(.2);p.stream(.6,values=(float('nan'),0.,0.));p.zero();results['nonfinite_timeout']=True
        p.handshake();p.stream(.2);p.stream(.6,values=(1.1,0.,0.));p.zero();results['out_of_range_timeout']=True
        p.handshake();p.stream(.2);p.stream(.3,enabled=False);p.zero();results['explicit_disable']=True
        p.handshake();p.stream(.2);p.spin(.5);p.zero();results['silence_timeout']=True
        # Mode transitions and calibration changes are commanded over a separate SITL MAVLink connection.
        mav=mavutil.mavlink_connection(args.mavlink,source_system=254)
        deadline=time.monotonic()+5
        while time.monotonic()<deadline:
            heartbeat=mav.recv_match(type='HEARTBEAT',blocking=True,timeout=.5)
            if heartbeat is not None and heartbeat.get_srcSystem()==1 and heartbeat.get_srcComponent()==1:break
        else:raise TimeoutError('No autopilot heartbeat on probe link')
        def mode(name):
            mav.mav.set_mode_send(1,mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,mav.mode_mapping()[name]);p.spin(1)
        def param(name,value):
            mav.mav.param_set_send(1,1,name.encode(),value,mavutil.mavlink.MAV_PARAM_TYPE_REAL32);p.spin(.4)
        p.handshake();p.stream(.2);mode('LOITER');p.zero();assert p.frame.state==4;results['mode_loss']=True
        mode('GUIDED');p.handshake();p.stream(.2)
        revision=p.frame.configuration_revision
        param('SERVO5_FUNCTION',4)
        p.zero();assert p.frame.configuration_revision>revision
        param('SERVO5_MIN',1000);param('SERVO5_TRIM',1400);param('SERVO5_MAX',2000);param('SERVO5_REVERSED',1)
        p.handshake();p.stream(.5);p.validate()
        assert p.frame.function[4]==4 and p.frame.reversed[4]==1
        assert p.frame.excitation[4]>0 and p.frame.delta[4]<0
        results['live_mapping_calibration_reversal']=True
        p.stream(.3,enabled=False);p.zero()
        # A deliberate invalid calibration must inhibit excitation atomically.
        param('SERVO5_TRIM',2500)
        p.stream(.3,enabled=False);p.stream(.3);p.zero();assert p.frame.state==4
        results['invalid_calibration']=True
        param('SERVO5_TRIM',1400);param('SERVO5_FUNCTION',0)
        mav.close()
    finally:
        if p.clock:p.stream(.25,enabled=False)
        p.destroy_node();rclpy.shutdown()
    print(json.dumps(results,indent=2))

if __name__=='__main__':main()
