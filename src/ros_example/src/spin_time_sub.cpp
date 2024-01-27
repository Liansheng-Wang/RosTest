#include <ros/ros.h>
#include <nav_msgs/Odometry.h>




double time_star;



void test_cb1(const nav_msgs::Odometry::ConstPtr& msg){
    int i = msg->pose.pose.position.x;
    double time = msg->header.stamp.toSec();
    std::cout << "1111:   "   << i << "    " << time - time_star <<std::endl;
}


void test_cb2(const nav_msgs::Odometry::ConstPtr& msg){
    int i = msg->pose.pose.position.x;
    double time = msg->header.stamp.toSec();
    std::cout << "2222:   "   << i << "    " << time - time_star <<std::endl;
}



int main(int argc, char** argv){
    ros::init(argc, argv, "spintime_sub_node");
    ros::NodeHandle nh;
    time_star = ros::Time::now().toSec();

    ros::Subscriber sub_odom = nh.subscribe<nav_msgs::Odometry>("/test1", 10, &test_cb1, ros::TransportHints().tcpNoDelay());
    ros::Subscriber sub_odom2 = nh.subscribe<nav_msgs::Odometry>("/test2", 10, &test_cb2, ros::TransportHints().tcpNoDelay());

    ros::spin();
}


// 结论：
// ROS 的 消息队列和发的时间戳没关系，而是和结束的时间有关！

