
# Data Discovery:
To show the data nicely in rviz and create the required transforms.

## File description:
### data_tf_broadcaster.cpp:
This node is broadcasting the required extra /tf frames 
then we can plot all the data 
in a nice manner in rviz.

The required /tf:
* gps
* velodyne

The following frames are already defined:
* base_link (for radar frame)
* radar (for topics /radar/points and /radar/range)

Velodyne frame can be defined over the base_link, 
gps needs further investigations. 
The node should exactly work like:
```$xslt
rosrun tf2_ros static_transform_publisher 0 0 0 0 0 0 base_link velodyne
```
### tf_velodyne_to_baselink.cpp
To find the correct position of the obstacle relative to capture car, we need to know the absoulte 
pose of the capture car (or relative to GPS frame)

Here the pose is calculated based on the postion and speed values of the capture car.

### tf_baselink_to_gps_using_position.cpp
Pose here is calculated based on the position only.

## Dependencies:
roscpp, tf2, tf2_ros

## Usage:
```$xslt
git clone https://github.com/didi-challenge-team-khodro/data_analysis.git
cd data_analysis
catkin_make
source devel/setup.sh
roslaunch data_discovery data_vis.launch rosbag_file:=path/of/bag/file
```
