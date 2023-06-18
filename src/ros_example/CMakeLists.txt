cmake_minimum_required(VERSION 3.20)
project(ros_example)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp rospy
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(spin_test src/spin_test.cpp)
target_link_libraries(spin_test
          ${catkin_LIBRARIES}
        )
