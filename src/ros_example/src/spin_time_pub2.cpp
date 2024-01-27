#include <ros/ros.h>
#include <nav_msgs/Odometry.h>


int main(int argc, char** argv){
    ros::init(argc, argv, "spintime_pub2_node");
    ros::NodeHandle nh;
    ros::Publisher pub_odom2 = nh.advertise<nav_msgs::Odometry>("/test2", 1);

    nav_msgs::Odometry odom;
    odom.header.frame_id = "map";
    odom.pose.pose.position.x = 0;
    int cout = 1;

    ros::Rate loop(4);

    while(ros::ok()){
        odom.pose.pose.position.x = cout;
        odom.header.stamp = ros::Time().fromSec(ros::Time().now().toSec() - 5.0);
        loop.sleep();
        pub_odom2.publish(odom);
        cout++;
    }
}