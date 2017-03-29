#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <sensor_msgs/PointCloud2.h>
#include <tf2/LinearMath/Quaternion.h>


void pointCloudCallBack(const sensor_msgs::PointCloud2& msg){//const sensor_msgs::PointCloud2& msg
    static tf2_ros::TransformBroadcaster tf_br;
    geometry_msgs::TransformStamped tf_stamped;

    tf_stamped.child_frame_id="velodyne";
    tf_stamped.header.frame_id ="base_link";
    tf_stamped.header.stamp = msg.header.stamp;
    tf_stamped.transform.translation.x = 0;
    tf_stamped.transform.translation.y = 0;
    tf_stamped.transform.translation.z = 0;

    tf2::Quaternion quat;
    quat.setRPY(0.0, 0.0, 0.0);
    tf_stamped.transform.rotation.x = quat.x();
    tf_stamped.transform.rotation.y = quat.y();
    tf_stamped.transform.rotation.z = quat.z();
    tf_stamped.transform.rotation.w = quat.w();
    tf_br.sendTransform(tf_stamped);
    ROS_INFO_STREAM("Spinning until killed publishing to world");
}


int main (int argc,char** argv){
    ros::init(argc,argv,"tf_velodyne_to_baselink");

    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("velodyne_points",100,&pointCloudCallBack);

    ros::spin();
    return 0;
}