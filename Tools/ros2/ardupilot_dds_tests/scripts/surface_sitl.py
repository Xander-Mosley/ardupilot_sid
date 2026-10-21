#!/usr/bin/env python3
"""Owned-process SITL experiment. Requires isolated ROS container + agent from README."""
import argparse
import json
import os
import shlex
from pathlib import Path
import subprocess
import time
from pymavlink import mavutil

ROOT=Path(__file__).resolve().parents[4]
WORKSPACE=ROOT.parent

class Flight:
    def __init__(self, connection):
        self.mav=mavutil.mavlink_connection(connection,source_system=255)
        self.last_heartbeat=0.;self.alt=0.;self.armed=False;self.mode=None;self.rc_throttle=1000
        self.messages=[]
    def pump(self, seconds=.1):
        end=time.monotonic()+seconds
        while time.monotonic()<end:
            if time.monotonic()-self.last_heartbeat>=.5:
                self.mav.mav.heartbeat_send(mavutil.mavlink.MAV_TYPE_GCS,mavutil.mavlink.MAV_AUTOPILOT_INVALID,0,0,0)
                self.mav.mav.rc_channels_override_send(1,1,1500,1500,self.rc_throttle,1500,1500,1500,1000,1500)
                self.last_heartbeat=time.monotonic()
            m=self.mav.recv_match(blocking=True,timeout=.05)
            if m is None:continue
            if m.get_type()=='HEARTBEAT':
                self.armed=bool(m.base_mode & mavutil.mavlink.MAV_MODE_FLAG_SAFETY_ARMED);self.mode=m.custom_mode
            elif m.get_type()=='GLOBAL_POSITION_INT':self.alt=m.relative_alt/1000
            elif m.get_type()=='STATUSTEXT':
                print(m.text,flush=True);self.messages.append(m.text)
    def wait(self,predicate,timeout,label):
        end=time.monotonic()+timeout
        while time.monotonic()<end:
            self.pump()
            if predicate():return
        raise TimeoutError(label)
    def parameter(self,name,value):
        self.mav.mav.param_set_send(1,1,name.encode(),value,mavutil.mavlink.MAV_PARAM_TYPE_REAL32)
        self.pump(.3)
    def mode_set(self,name):
        mode=self.mav.mode_mapping()[name]
        self.mav.mav.set_mode_send(1,mavutil.mavlink.MAV_MODE_FLAG_CUSTOM_MODE_ENABLED,mode)
        self.wait(lambda:self.mode==mode,10,'mode '+name)
    def takeoff(self):
        # Same TAKEOFF sequence as AutoTestPlane.takeoff_in_TAKEOFF:
        # set altitude, wait ready, arm, wait relative altitude. No forced arming.
        self.mav.wait_heartbeat(timeout=30)
        self.mav.mav.request_data_stream_send(1,1,mavutil.mavlink.MAV_DATA_STREAM_ALL,10,1)
        self.pump(10)
        self.parameter('TKOFF_ALT',100)
        self.mode_set('TAKEOFF')
        for _ in range(30):
            self.mav.mav.command_long_send(1,1,mavutil.mavlink.MAV_CMD_COMPONENT_ARM_DISARM,0,1,0,0,0,0,0,0)
            self.pump(2)
            if self.armed:break
        if not self.armed:raise RuntimeError('Normal arming failed')
        self.rc_throttle=1800
        self.wait(lambda:self.alt>=80,120,'takeoff altitude')
        self.mode_set('GUIDED');self.pump(8)

def main():
    p=argparse.ArgumentParser(description=__doc__)
    p.add_argument('--airframe',choices=['conventional','vtail','elevon'],default='conventional')
    p.add_argument('--container',default='sid-validation');p.add_argument('--output',required=True)
    p.add_argument('--rate',type=float,help='Override example publication rate; preserve safety deadlines')
    p.add_argument('--individual-axes',action='store_true',help='Run chirp and multisine separately on roll, pitch and yaw')
    p.add_argument('--binary',default=str(ROOT/'build/sitl/bin/arduplane'))
    a=p.parse_args();out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=True)
    if a.rate is not None and not 10<=a.rate<=400:p.error('rate must be in [10,400] Hz')
    experiments=([f'{signal}_{axis}' for axis in ('roll','pitch','yaw') for signal in ('chirp','multisine')]
                 if a.individual_axes else ['chirp','multisine','multisine_all_axes'])
    configs=ROOT/'Tools/ros2/ardupilot_sitl/config/surface_excitation'
    defaults=[ROOT/'Tools/autotest/models/plane.parm',configs/'conventional.parm']
    if a.airframe!='conventional':defaults.append(configs/(a.airframe+'.parm'))
    # A single complete defaults file also preserves deferred DDS parameter loading
    # in this fork (its multi-file completion flag reflects only the final file).
    params={}
    for path in defaults:
        for line in path.read_text().splitlines():
            fields=line.split('#',1)[0].split()
            if fields:params[fields[0]]=' '.join(fields[1:])
    combined=out/'defaults.parm'
    combined.write_text(''.join(f'{key} {value}\n' for key,value in params.items()))
    model='plane' if a.airframe=='conventional' else 'plane-'+a.airframe
    command=[a.binary,'--model',model,'--speedup','1','--wipe','--home','-35.362938,149.165085,584,353',
             '--serial0','tcp:5780','--serial1','tcp:5782','--defaults',str(combined)]
    (out/'launch.json').write_text(json.dumps(command,indent=2))
    firmware_log=(out/'sitl.txt').open('w')
    sitl=subprocess.Popen(command,cwd=out,stdout=firmware_log,stderr=subprocess.STDOUT)
    results={};flight=None;bag=None
    bag_path='/work/'+str(out.relative_to(WORKSPACE))+'/rosbag'
    bag_command='source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; setsid /work/ros2_sid/ros2_sid/scripts/record_surface_excitation.sh '+bag_path+' & echo $! > /tmp/sid-bag.pid; wait'
    bag_log=(out/'rosbag.txt').open('w')
    bag=subprocess.Popen(['docker','exec','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',bag_command],stdout=bag_log,stderr=subprocess.STDOUT)
    try:
        time.sleep(3);flight=Flight('tcp:127.0.0.1:5780');flight.takeoff()
        for experiment in experiments:
            # /work is the repository mount in the isolated ROS container.
            source=experiment.split('_')[0] if a.individual_axes else experiment
            spec=json.loads((WORKSPACE/'ros2_sid/ros2_sid/config/surface_excitation'/(source+'.json')).read_text())
            if a.individual_axes:
                axis=experiment.split('_')[1]
                spec['axes']={axis:spec['axes']['roll']}
            if a.rate is not None:spec['rate']=a.rate
            experiment_path=out/(experiment+'.json')
            experiment_path.write_text(json.dumps(spec,indent=2)+'\n')
            container_experiment='/work/'+str(experiment_path.relative_to(WORKSPACE))
            logfile=(out/(experiment+'.txt')).open('w')
            launch=['docker','exec','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',
                    'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '
                    'ros2 run ros2_sid run_mission_SITL.py --interface dds --autostart --wait-timeout 180 '
                    f'--experiment {shlex.quote(container_experiment)} '
                    f'--command-log /tmp/{experiment}-commands.csv']
            proc=subprocess.Popen(launch,stdout=logfile,stderr=subprocess.STDOUT)
            end=time.monotonic()+220
            while proc.poll() is None and time.monotonic()<end:flight.pump()
            if proc.poll() is None:proc.terminate();raise TimeoutError('publisher')
            logfile.close();results[experiment]=proc.returncode==0
            subprocess.run(['docker','cp',f'{a.container}:/tmp/{experiment}-commands.csv',str(out/(experiment+'-commands.csv'))],check=True)
            if proc.returncode:raise RuntimeError(f'{experiment} publisher failed')
            flight.pump(2)
        probe_log=(out/'probe.txt').open('w')
        probe=subprocess.Popen(['docker','exec','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',
            'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '
            'python3 /work/ardupilot_sid/Tools/ros2/ardupilot_dds_tests/scripts/surface_probe.py'],stdout=probe_log,stderr=subprocess.STDOUT)
        deadline=time.monotonic()+90
        while probe.poll() is None and time.monotonic()<deadline:flight.pump()
        if probe.poll() is None:probe.terminate();raise TimeoutError('safety probe')
        probe_log.close();results['safety_probe']=probe.returncode==0
        if probe.returncode:raise RuntimeError('DDS safety probe failed')
        flight.mode_set('LOITER');flight.pump(2)
        results['mode_change']=True
    finally:
        if bag is not None:
            subprocess.run(['docker','exec','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c','kill -INT -- -$(cat /tmp/sid-bag.pid)'],check=False)
            try:bag.wait(timeout=15)
            except subprocess.TimeoutExpired:bag.terminate();bag.wait()
            bag_log.close()
        sitl.terminate()
        try:sitl.wait(timeout=10)
        except subprocess.TimeoutExpired:sitl.kill();sitl.wait()
        firmware_log.close();(out/'execution.json').write_text(json.dumps(results,indent=2))
    # Validate each complete waveform from the bag after the recorder closes.
    container_out='/work/'+str(out.relative_to(WORKSPACE))
    analysis=['python3','/work/ros2_sid/ros2_sid/scripts/plot_surface_excitation.py',bag_path,
              '--output',container_out+'/plots','--compare-dataflash',container_out+'/logs/00000001.BIN']
    for experiment in experiments:
        analysis+=['--command-log',container_out+'/'+experiment+'-commands.csv']
    with (out/'analysis.txt').open('w') as stream:
        completed=subprocess.run(['docker','exec',a.container,'bash','-c',
            'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; '
            'export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '+shlex.join(analysis)],
            stdout=stream,stderr=subprocess.STDOUT)
    results['bag_validation']=completed.returncode==0
    (out/'execution.json').write_text(json.dumps(results,indent=2))
    print(json.dumps(results,indent=2))
    if not results['bag_validation']:raise RuntimeError('Recorded output validation failed')

if __name__=='__main__':main()
