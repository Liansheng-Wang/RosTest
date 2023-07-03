

#include <vector>

#include <sensor_msgs/PointCloud2.h>
#include <pcl_conversions/pcl_conversions.h>

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>


void test_ptr(){
  pcl::PointCloud<pcl::PointXYZINormal>::Ptr cloud_n;

  std::vector<pcl::PointCloud<pcl::PointXYZINormal>> clouds_vec;

  cloud_n.reset(new pcl::PointCloud<pcl::PointXYZINormal>());

  pcl::PointXYZINormal pointn;

  pointn.x = 1;
  pointn.y = 1;
  pointn.z = 1;

  cloud_n->points.push_back(pointn);

  clouds_vec.push_back(*cloud_n);

  cloud_n->clear();

  std::cout << clouds_vec.size() << std::endl;

  if(clouds_vec.size() > 0){
    std::cout << clouds_vec.at(0).points.at(0) << std::endl;
  }
}



int main(){
  test_ptr();
}