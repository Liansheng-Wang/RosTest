#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <Eigen/Core>
#include <Eigen/Geometry>


int main(int argc, char** argv){
    ros::init(argc, argv, "ax_xb_node");
    ros::NodeHandle nh;
    
    ros::Publisher pub_odom = nh.advertise<nav_msgs::Odometry>("/test/odom", 1);
    ros::Publisher pub_odom2 = nh.advertise<nav_msgs::Odometry>("/test/odom2", 1);

    Eigen::Quaterniond q1(0.9238795,0.3826834, 0, 0);


    const Eigen::Quaterniond q2(-0.5, 0.5, -0.5, 0.5);
    const Eigen::Quaterniond q2_inverse(-0.5, -0.5, 0.5, -0.5);
    Eigen::Quaterniond q3 = q2 * q1 * q2.inverse();

    Eigen::Quaterniond q4 = q2.inverse();

    std::cout << q1.coeffs().transpose() << std::endl;
    std::cout << q4.coeffs().transpose() << std::endl;


    nav_msgs::Odometry odom;
    odom.header.frame_id = "map";
    odom.pose.pose.position.x = 0;
    odom.pose.pose.position.y = 0;
    odom.pose.pose.position.z = 0;
    odom.pose.pose.orientation.w = q3.w();
    odom.pose.pose.orientation.x = q3.x();
    odom.pose.pose.orientation.y = q3.y();
    odom.pose.pose.orientation.z = q3.z();

    ros::Rate loop(5);


    while(ros::ok()){
        odom.header.stamp = ros::Time().now();
        pub_odom2.publish(odom);
        loop.sleep();
    }
}
