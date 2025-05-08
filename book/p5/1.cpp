#include <iostream>
#include <numbers>

float circarea(float radius) { return std::numbers::pi * radius * radius; }

int main() {
    float radius;

    std::cout << "Radius: >> ";
    std::cin >> radius;

    std::cout << "S = " << circarea(radius) << std::endl;
    return 0;
}
