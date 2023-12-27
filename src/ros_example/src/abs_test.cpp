
#include <cmath>
#include <iostream>


int main(){
  float a = 0.5;
  float b = -0.3;

  std::cout << std::abs(a) << std::endl;
  std::cout << std::fabs(a) << std::endl;

  std::cout << std::abs(b) << std::endl;
  std::cout << std::fabs(b) << std::endl;

  return 0;
}