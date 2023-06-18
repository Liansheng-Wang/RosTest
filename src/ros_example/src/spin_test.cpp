/**
 * @file spin_test.cpp
 * @author Wangliansheng
 * @brief 
 * @version 0.1
 * @date 2023-06-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <ctime>
#include <thread>
#include <ros/ros.h>
#include <ros/callback_queue.h>
#include <std_msgs/Int16.h>
#include <std_msgs/String.h>


class TestA{
private:
  ros::NodeHandle nh_;
  ros::Publisher pub_traj_;
  ros::Subscriber sub_obs_;
  ros::CallbackQueue self_queue_;
  std::thread* thread_run_ = nullptr;

public:
  TestA()
  {
    nh_.setCallbackQueue(&self_queue_);
    sub_obs_ = nh_.subscribe("/test/channel", 1,
                              &TestA::test_cb, this,
                              ros::TransportHints().tcpNoDelay());

    thread_run_ = new std::thread(std::bind(&TestA::run, this));
  }

  ~TestA(){
    thread_run_ = nullptr;
  }


private:
  void test_cb(const std_msgs::Int16::ConstPtr& msg){
    std::cout << "TestA: AAAAAA  " << std::endl;
  }

  void run()
  {
    std::cout << "TestA: RUN " << std::endl;  
    ros::Rate loop(5);
    while(ros::ok()){
      self_queue_.callAvailable();
      loop.sleep();
    }
  }
};


class TestB{
private:
  ros::NodeHandle nh_;
  ros::Publisher pub_traj_;
  ros::Subscriber sub_obs_;
  ros::CallbackQueue self_queue_;
  std::thread* thread_run_ = nullptr;
  
public:
  TestB()
  {
    nh_.setCallbackQueue(&self_queue_);
    sub_obs_ = nh_.subscribe("/test/channel", 1,
                              &TestB::test_cb, this,
                              ros::TransportHints().tcpNoDelay());

    thread_run_ = new std::thread(std::bind(&TestB::run, this));
  }

  ~TestB(){
    thread_run_ = nullptr;
  }


private:
  void test_cb(const std_msgs::Int16::ConstPtr& msg){
    std::cout << "TestB: BBBBBB  " << std::endl;
  }

  void run()
  {
    std::cout << "TestB: RUN " << std::endl;  
    ros::Rate loop(5);
    while(ros::ok()){
      self_queue_.callAvailable();
      loop.sleep();
    }
  }
};


int main(int argc, char** argv){
  ros::init(argc, argv, "test_spin_node");
  ros::NodeHandle nh;

  TestB testb_;
  TestA testa_;

  ros::Publisher test_pub = nh.advertise<std_msgs::Int16>("/test/channel", 10);

  std_msgs::Int16 msg;
  msg.data = 1;

  ros::Rate loop(5);
  while(ros::ok()){
    std::cout << " test_pub " << std::endl;
    test_pub.publish(msg);
    loop.sleep();
  }
  return 0;
}