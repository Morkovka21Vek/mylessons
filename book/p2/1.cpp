#include <iostream>

int main() {

    // значение из учебника страница 88
    const float gal = 7.481;
    float inp;
    float out;

    std::cout << "Enter galons please" << std::endl << "Gal: >> ";
    std::cin >> inp;

    out = inp / gal;

    std::cout << "In " << inp << " gallons " << out << " foots" << std::endl;

    return 0;
}
