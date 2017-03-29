
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

#### Dependencies:
roscpp, tf2, tf2_ros

## Usage:
```$xslt
roslaunch data_discovery data_vis.launch rosbag_file:=/media/yousof/Volume/SDC/Challenges/DIDI/Dataset/data/approach_3.bag
```
