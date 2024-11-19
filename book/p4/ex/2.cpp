#include <iostream>

struct point {
  int x;
  int y;
};

int main() {
  point p1, p2, p3;

  std::cout << "Введите координаты первой точки через пробел: ";
  std::cin >> p1.x >> p1.y;

  std::cout << "Введите координаты второй точки через пробел: ";
  std::cin >> p2.x >> p2.y;

  p3.x = p1.x + p2.x;
  p3.y = p1.y + p2.y;

  std::cout << "Сумма координат двух точек равна: " << p3.x << ", " << p3.y << std::endl;

  return 0;
}

