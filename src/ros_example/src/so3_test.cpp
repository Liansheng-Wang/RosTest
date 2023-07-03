
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>


void test0(){
  /**
   * 雷达L1、L2, IMU I0
   * 
   */

  Eigen::Vector3d L2_to_L1, L1_to_I0, L2_to_I0;

  Eigen::Matrix3d R_L2_to_L1, R_L1_to_T0, R_L2_to_T0;

  L2_to_L1 << -0.9125, 0.0138033, -0.0184701;
  R_L2_to_L1 << -0.999306, -0.0233402, -0.0290415,
                  0.0231166, -0.999701, 0.00801259,
                  -0.0292198, 0.0073357, 0.999546;
  
  L1_to_I0 << 0.426260, 0.000913, -0.194509;
  R_L1_to_T0 << 0.998738, -0.044008, 0.024217,
                0.044746, 0.998523, -0.030817,
               -0.022825, 0.031861, 0.999232;

  
  R_L2_to_T0 = R_L1_to_T0 * R_L2_to_L1;

  L2_to_I0 = R_L1_to_T0 * L2_to_L1 + L1_to_I0;

  
  std::cout << L2_to_I0.transpose() << std::endl << std::endl;


  std::cout << R_L2_to_T0 << std::endl;


}




int main(){
  test0();
}