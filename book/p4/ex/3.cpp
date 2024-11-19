#include <iostream>

struct Distance
{
	int feet;
	float inches;
};

struct Volume {
  Distance x;
  Distance y;
  Distance z;
};

int main() {

  Volume vol = {{2, 2}, {3, 3}, {5, 5}};

  float x = vol.x.feet + vol.x.inches/12;
  float y = vol.y.feet + vol.y.inches/12;
  float z = vol.z.feet + vol.z.inches/12;

  std::cout << "Объём равен " << x*y*z << " кубических футов" << std::endl;

  return 0;
}
