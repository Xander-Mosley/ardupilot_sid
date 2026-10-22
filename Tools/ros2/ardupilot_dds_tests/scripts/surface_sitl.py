#!/usr/bin/env python3
"""Owned-process SITL experiment. Requires isolated ROS container + agent from README."""
import argparse
import json
import os
import shlex
import shutil
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
            if m.get_srcSystem()!=1 or m.get_srcComponent()!=1:continue
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
    p.add_argument('--interactive-library',action='store_true',help='Exercise the default CSV mission library through console stdin')
    p.add_argument('--straight-flight',action='store_true')
    p.add_argument('--only-experiment')
    p.add_argument('--exit-active',choices=['quit','stop','sigint','sigterm','cycle'],help='Interrupt after two seconds of ACTIVE for recovery verification')
    p.add_argument('--dds-domain',type=int,default=0)
    p.add_argument('--dds-port',type=int,default=2021)
    p.add_argument('--binary',default=str(ROOT/'build/sitl/bin/arduplane'))
    a=p.parse_args();out=Path(a.output).resolve();out.mkdir(parents=True,exist_ok=True)
    if a.exit_active and not (a.interactive_library and a.straight_flight):p.error('--exit-active requires --interactive-library --straight-flight')
    if a.rate is not None and not 10<=a.rate<=400:p.error('rate must be in [10,400] Hz')
    if a.interactive_library:
        a.individual_axes=True
        library=WORKSPACE/'ros2_sid/ros2_sid/ros2_sid/setup/mission_library'
        selected=json.loads((library/'current_mission.json').read_text())['subfolder']
        shutil.copytree(library/selected,out/'mission_library')
        shutil.copy2(library/'current_mission.json',out/'current_mission.json')
    experiments=([f'{signal}_{axis}' for axis in ('roll','pitch','yaw') for signal in ('chirp','multisine')]
                 if a.individual_axes else ['chirp','multisine','multisine_all_axes'])
    all_experiments=list(experiments)
    if a.only_experiment:experiments=[a.only_experiment] if a.only_experiment in experiments else p.error('unknown experiment')
    (out/'test_options.json').write_text(json.dumps(vars(a),indent=2))
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
    if a.straight_flight:
        params['SR1_POSITION']='10'
        params['SERIAL2_PROTOCOL']='2'
    params['DDS_DOMAIN_ID']=str(a.dds_domain)
    params['DDS_UDP_PORT']=str(a.dds_port)
    combined=out/'defaults.parm'
    combined.write_text(''.join(f'{key} {value}\n' for key,value in params.items()))
    model='plane' if a.airframe=='conventional' else 'plane-'+a.airframe
    command=[a.binary,'--model',model,'--speedup','1','--wipe','--home','-35.362938,149.165085,584,353',
             '--serial0','tcp:5780','--serial1','tcp:5782','--serial2','tcp:5783','--defaults',str(combined)]
    (out/'launch.json').write_text(json.dumps(command,indent=2))
    firmware_log=(out/'sitl.txt').open('w')
    sitl=subprocess.Popen(command,cwd=out,stdout=firmware_log,stderr=subprocess.STDOUT)
    results={};flight=None;bag=None;mavros=None;mavros_log=None;proc=None
    bag_path='/work/'+str(out.relative_to(WORKSPACE))+'/rosbag'
    bag_command='source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; setsid /work/ros2_sid/ros2_sid/scripts/record_surface_excitation.sh '+bag_path+' & echo $! > /tmp/sid-bag.pid; wait'
    bag_log=(out/'rosbag.txt').open('w')
    bag=subprocess.Popen(['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',bag_command],stdout=bag_log,stderr=subprocess.STDOUT)
    try:
        time.sleep(3);flight=Flight('tcp:127.0.0.1:5780');flight.takeoff()
        if a.straight_flight:
            mavros_log=(out/'mavros.txt').open('w')
            mavros=subprocess.Popen(['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}',a.container,'bash','-c',
                'source /opt/ros/humble/setup.bash; setsid ros2 run mavros mavros_node --ros-args -p fcu_url:=tcp://127.0.0.1:5782 --params-file /work/ros2_sid/ros2_sid/config/surface_excitation/mavros_straight.yaml & echo $! > /tmp/sid-mavros.pid; wait'],stdout=mavros_log,stderr=subprocess.STDOUT)
            flight.pump(5)
        for experiment in experiments:
            experiment_index=all_experiments.index(experiment)
            exit_action=('quit','stop','sigint','sigterm')[experiment_index%4] if a.exit_active=='cycle' else a.exit_active
            if a.straight_flight:
                flight.mode_set('GUIDED');flight.pump(3)
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
            launch=['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',
                    'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '
                    'ros2 run ros2_sid run_mission_SITL.py --interface dds --autostart --wait-timeout 180 '
                    f'--experiment {shlex.quote(container_experiment)} '
                    f'--command-log /tmp/{experiment}-commands.csv']
            if a.straight_flight:
                launch[-1]+=' --straight-flight /work/ros2_sid/ros2_sid/config/surface_excitation/straight_flight_sitl.json'
            else:
                launch[-1]+=' --no-straight-flight'
            if a.interactive_library:
                launch.insert(2, '-i')
                launch[-1]=launch[-1].replace('--autostart ', '').replace(f'--experiment {shlex.quote(container_experiment)} ', '')
            proc=subprocess.Popen(launch,stdout=logfile,stderr=subprocess.STDOUT,
                                  stdin=subprocess.PIPE if a.interactive_library else None, text=True)
            if a.interactive_library:
                proc.stdin.write(f'list\nselect {experiment_index}\nstart\n');proc.stdin.flush()
            quit_sent=False;active_at=None
            end=time.monotonic()+300
            while proc.poll() is None and time.monotonic()<end:
                flight.pump()
                console_text=(out/(experiment+'.txt')).read_text()
                if a.exit_active and 'Straight flight: ACTIVE:' in console_text and active_at is None:active_at=time.monotonic()
                if a.exit_active and active_at is not None and time.monotonic()-active_at>2 and not quit_sent:
                    if exit_action in ('sigint','sigterm'):
                        script="import os,signal; from pathlib import Path; me=os.getpid(); target=b'/tmp/"+experiment+"-commands.csv'; "+"\nfor p in Path('/proc').iterdir():\n if p.name.isdigit() and int(p.name)!=me:\n  try: args=(p/'cmdline').read_bytes().split(bytes([0]))\n  except OSError: continue\n  if target in args and any(x.endswith(b'/run_mission_SITL.py') for x in args[:2]): os.kill(int(p.name),signal.SIGINT)"
                        if exit_action=='sigterm':script=script.replace('signal.SIGINT','signal.SIGTERM')
                        subprocess.run(['docker','exec',a.container,'python3','-c',script],check=True)
                    else:
                        proc.stdin.write(exit_action+'\nquit\n');proc.stdin.flush()
                    quit_sent=True
                if a.interactive_library and not quit_sent and any(message in (out/(experiment+'.txt')).read_text() for message in ('Maneuver complete', 'publication jitter exceeds two periods', 'Firmware timeout/fault', 'Firmware did not authorize', 'No fresh AP clock','Straight-flight settling/setup timeout','Navigation command ACK timeout','Navigation command rejected','Straight-flight authorization/telemetry lost','Straight-flight envelope exceeded')):
                    flight.pump(1)
                    proc.stdin.write('stop\nquit\n');proc.stdin.flush();quit_sent=True
            if proc.poll() is None:proc.terminate();raise TimeoutError('publisher')
            logfile.close();results[experiment]=proc.returncode==0
            subprocess.run(['docker','cp',f'{a.container}:/tmp/{experiment}-commands.csv',str(out/(experiment+'-commands.csv'))],check=True)
            if a.straight_flight:
                subprocess.run(['docker','cp',f'{a.container}:/tmp/{experiment}-commands.csv.straight.jsonl',str(out/(experiment+'.straight.jsonl'))],check=True)
                flight.pump(1)
                results[experiment+'_recovery']=flight.mode==flight.mav.mode_mapping()['LOITER']
                if not results[experiment+'_recovery']:raise RuntimeError('LOITER recovery not confirmed')
            if proc.returncode:raise RuntimeError(f'{experiment} publisher failed')
            flight.pump(2)
        if a.straight_flight:
            flight.mode_set('GUIDED');flight.pump(5)
        probe_log=(out/'probe.txt').open('w')
        probe=subprocess.Popen(['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c',
            'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '
            'python3 /work/ardupilot_sid/Tools/ros2/ardupilot_dds_tests/scripts/surface_probe.py'+(' --mavlink tcp:127.0.0.1:5783' if a.straight_flight else '')],stdout=probe_log,stderr=subprocess.STDOUT)
        deadline=time.monotonic()+90
        while probe.poll() is None and time.monotonic()<deadline:flight.pump()
        if probe.poll() is None:probe.terminate();raise TimeoutError('safety probe')
        probe_log.close();results['safety_probe']=probe.returncode==0
        if probe.returncode:raise RuntimeError('DDS safety probe failed')
        flight.mode_set('LOITER');flight.pump(2)
        results['mode_change']=True
    finally:
        # Keep navigation/telemetry available while an owned publisher exits,
        # including failures in the harness itself.
        if proc is not None and proc.poll() is None:
            if proc.stdin is not None:
                try:proc.stdin.write('quit\n');proc.stdin.flush()
                except (BrokenPipeError, OSError):pass
            deadline=time.monotonic()+10
            while proc.poll() is None and time.monotonic()<deadline:
                if flight is not None:flight.pump()
                else:time.sleep(.1)
        if mavros is not None:
            subprocess.run(['docker','exec',a.container,'bash','-c','kill -INT -- -$(cat /tmp/sid-mavros.pid)'],check=False)
            try:mavros.wait(timeout=10)
            except subprocess.TimeoutExpired:mavros.terminate();mavros.wait()
            mavros_log.close()
        if bag is not None:
            subprocess.run(['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}','-e','FASTRTPS_DEFAULT_PROFILES_FILE=/work/ros2_sid/ros2_sid/config/surface_excitation/fastdds_udp.xml',a.container,'bash','-c','kill -INT -- -$(cat /tmp/sid-bag.pid)'],check=False)
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
    if a.straight_flight:analysis+=['--straight-flight']
    for experiment in experiments:
        analysis+=['--command-log',container_out+'/'+experiment+'-commands.csv']
    with (out/'analysis.txt').open('w') as stream:
        completed=subprocess.run(['docker','exec','-e',f'ROS_DOMAIN_ID={a.dds_domain}',a.container,'bash','-c',
            'source /opt/ros/humble/setup.bash; source /tmp/install/setup.bash; '
            'export PYTHONPATH=/work/ros2_sid/ros2_sid:$PYTHONPATH; '+shlex.join(analysis)],
            stdout=stream,stderr=subprocess.STDOUT)
    results['bag_validation']=completed.returncode==0
    (out/'execution.json').write_text(json.dumps(results,indent=2))
    print(json.dumps(results,indent=2))
    if not results['bag_validation']:raise RuntimeError('Recorded output validation failed')

if __name__=='__main__':main()
