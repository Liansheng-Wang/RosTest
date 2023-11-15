
#include <ctime>
#include <thread>
#include <ros/ros.h>
#include <Eigen/Core>



void test_rate(){
  double sleep_rate = 20;
  ros::Rate loop(sleep_rate);
  double t1 = ros::Time().now().toSec();
  double t2 = t1;
  while(ros::ok()){
    t1 = ros::Time().now().toSec(); 
    loop.sleep();
    if (sleep_rate >= 0.2){
        sleep_rate -= 0.1;
    }
    loop = ros::Rate(sleep_rate);
    t2 = ros::Time().now().toSec(); 
    std::cout << t2 - t1 << std::endl;
  }
}

int main(int argc, char** argv){
  ros::init(argc, argv, "test_rate_sleep");
  ros::NodeHandle nh;
  std::thread visual_map(&test_rate);
  ros::spin();
  return 0;
}