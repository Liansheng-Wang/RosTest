cmake_minimum_required(VERSION 3.16)
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

add_executable(kd_tree_test src/kd_tree.cpp)
target_link_libraries(kd_tree_test
          ${catkin_LIBRARIES}
          tbb 
        )

# add_executable(tcp_server src/tcp_test/tcp_server.cpp)
# target_link_libraries(tcp_server
#           ${catkin_LIBRARIES}
#         )     
        
# add_executable(tcp_client src/tcp_test/tcp_client.cpp)
# target_link_libraries(tcp_client
#           ${catkin_LIBRARIES}
#         )

add_executable(rate_sleep_test src/rate_sleep_test.cpp)
target_link_libraries(rate_sleep_test
          ${catkin_LIBRARIES}
        )

add_executable(abs_test src/abs_test.cpp)


add_executable(spin_time_pub src/spin_time_pub.cpp)
target_link_libraries(spin_time_pub
          ${catkin_LIBRARIES}
        )
add_executable(spin_time_pub2 src/spin_time_pub2.cpp)
target_link_libraries(spin_time_pub2
          ${catkin_LIBRARIES}
        )

add_executable(spin_time_sub src/spin_time_sub.cpp)
target_link_libraries(spin_time_sub
          ${catkin_LIBRARIES}
        )