cmake_minimum_required(VERSION 3.20)
project(ros_example)

add_compile_options(-std=c++17)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  pcl_conversions
)

find_package(PCL REQUIRED)

catkin_package(
  CATKIN_DEPENDS roscpp rospy
)

###########
## Build ##
###########

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${PCL_INCLUDE_DIRS}
)

link_directories(
  ${PCL_LIBRARY_DIRS}
)

add_executable(spin_test src/spin_test.cpp)
target_link_libraries(spin_test
          ${catkin_LIBRARIES}
        )

add_executable(pcl_test src/pcl_test.cpp)
target_link_libraries(pcl_test
          ${catkin_LIBRARIES}
          ${PCL_LIBRARIES}
        )       
           
add_executable(so3_test src/so3_test.cpp)
target_link_libraries(so3_test
          ${catkin_LIBRARIES}
        )       