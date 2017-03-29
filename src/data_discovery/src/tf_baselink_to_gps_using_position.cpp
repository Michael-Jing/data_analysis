#include <ros/ros.h>
#include <tf2_ros/transform_broadcaster.h>
#include <nav_msgs/Odometry.h>
#include <tf2/LinearMath/Quaternion.h>


void gpsCallBack(const nav_msgs::Odometry& msg){//const sensor_msgs::PointCloud2& msg
    static tf2_ros::TransformBroadcaster tf_br;
    geometry_msgs::TransformStamped tf_stamped;

    tf_stamped.child_frame_id="base_link";
    tf_stamped.header.frame_id ="gps";
    tf_stamped.header.stamp = msg.header.stamp;
    tf_stamped.transform.translation.x = msg.pose.pose.position.x;
    tf_stamped.transform.translation.y = msg.pose.pose.position.y;
    tf_stamped.transform.translation.z = 0;

    static int idx = 0, min_seq;
    static float pre_x= 0, pre_y=0;
    float delta_x = msg.pose.pose.position.x - pre_x ,delta_y = msg.pose.pose.position.y - pre_y;
    pre_x = msg.pose.pose.position.x;
    pre_y = msg.pose.pose.position.y;

    if (idx == 0)
        min_seq = msg.header.seq;

    if (msg.header.seq > min_seq){
        tf2::Quaternion quat;
        quat.setRPY(0.0, 0.0, atan2(delta_y, delta_x));
        tf_stamped.transform.rotation.x = quat.x();
        tf_stamped.transform.rotation.y = quat.y();
        tf_stamped.transform.rotation.z = quat.z();
        tf_stamped.transform.rotation.w = quat.w();
        tf_br.sendTransform(tf_stamped);
        ROS_INFO_STREAM("Spinning until killed publishing to world");
    }
    idx += 1;
}


int main (int argc,char** argv){
    ros::init(argc,argv,"tf_baselink_to_gps_using_position");

    ros::NodeHandle node;
    ros::Subscriber sub = node.subscribe("gps/rtkfix",100,&gpsCallBack);

    ros::spin();
    return 0;
}