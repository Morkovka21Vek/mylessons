#include "keyboard.hpp"
#include "tollBooth.hpp"
#include <iostream>

int main() {
    tollBooth tb;
    std::cout << "Press y(pay) or n(nopay)" << std::endl
              << "ESC to exit" << std::endl;

    char key;
    do {
        key = kbhit();
        switch (key) {
        case 'y':
            tb.payingCar();
            break;
        case 'n':
            tb.nopayCar();
            break;
        case EOF:
            break;
        case 27:
            break;
        default:
            std::cout << "Unknown key! Press ESC to exit" << std::endl;
        }
    } while (key != 27);
    std::cout << tb << std::endl;
    return 0;
}
