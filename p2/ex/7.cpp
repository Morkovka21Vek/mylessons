#include <iostream>

int main() {
    std::cout << "C: >>>";
    float tempF, tempC;
    std::cin >> tempC;
    tempF = tempC * 9 / 5 + 32;
    std::cout << "F >>" << tempF << std::endl;
    return 0;
}
