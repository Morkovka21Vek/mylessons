#include "Int.hpp"
#include <iostream>
int main() {
    Int num1 = 10;
    Int num2 = -1;

    std::cout << num1 << " + " << num2 << " = " << num1 + num2 << std::endl;

    Int i1 = 1073941823;
    Int i2 = 1073941850;
    num1 = i1 + i2;

    std::cout << i1 << " + " << i2 << " = " << num1 << std::endl;

    return 0;
}
