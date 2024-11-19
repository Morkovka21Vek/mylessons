#include <iostream>

int main() {
    float tempF, tempC;

    std::cout << "Пожалуйста введите темпиратуру в градусах по цельсию: \n>>> ";
    std::cin >> tempC;

	// Эта формула представлена в учебнике на станице 89
    tempF = tempC * 9 / 5 + 32;
    std::cout << "Темпиратура в градусах по фаренгейту: >> " << tempF << std::endl;

    return 0;
}
