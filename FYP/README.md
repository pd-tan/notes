# Run sim
`./follow_me_dev/wra_sim/build/bin/app_vbot_scout_uwb vcan0 simple2.png 0.02`

# Scout Sim based 
`ros2 launch scout_bringup nav_prototype-wrasim-base.launch.py `
# Run Map Server 
`ros2 run nav2_map_server map_server --ros-args -p yaml_filename:="/home/tan/sim_map.yaml"`

`ros2 run nav2_util lifecycle_bringup map_server`

# Run map request and publisher node
`ros2 run map_publisher map_publisher`
#


`launch scout_slamtoolbox wrasim_map_server.launch.py`


`ros2 launch scout_rosnavigation navigation-wra_sim.launch.py`


`ros2 launch scout_description wrasim_description.launch.py `


`./build/bin/app_vbot_ros2bridge_scout`

`./bin/app_vbot_scout_pos vcan0 simple2.png 0.02`


`ros2 run nav2_util lifecycle_bringup map_server`

`ros2 launch map_publisher map_publisher.launch.py`