"""Fixed-wing DDS SITL; no physical serial devices or automatic arming."""
from pathlib import Path
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    config=Path(get_package_share_directory('ardupilot_sitl'))/'config'/'surface_excitation'
    return LaunchDescription([
        DeclareLaunchArgument('binary',default_value='arduplane'),
        DeclareLaunchArgument('model',default_value='plane'),
        DeclareLaunchArgument('defaults',default_value=','.join((str(config.parent/'models'/'plane.parm'),str(config/'conventional.parm')))),
        ExecuteProcess(cmd=[LaunchConfiguration('binary'),'--model',LaunchConfiguration('model'),
                            '--speedup','1','--defaults',LaunchConfiguration('defaults'),
                            '--home','-35.362938,149.165085,584,353','--serial0','tcp:5760'],output='screen'),
    ])
