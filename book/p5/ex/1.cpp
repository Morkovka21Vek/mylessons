#include <iostream>

float circarea(float radius) {
    const float PI = 3.14159F;
    return PI * radius * radius;
}

int main() {
    float radius;

    std::cout << "Radius: >> ";
    std::cin >> radius;

    std::cout << "S = " << circarea(radius) << std::endl;
    return 0;
}
