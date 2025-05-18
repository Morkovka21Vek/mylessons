#include "tollBooth.hpp"
#include "keyboard.hpp"
#include <iostream>

int main() {
    tollBooth tb;
    std::cout << "Press y(pay) or n(nopay)" << std::endl
              << "ESC to exit" << std::endl;

    std::pair<bool,char> key;

    do {
        key = kbhit();
        if (key.first) {
            switch (key.second) {
                case 'y':
                    tb.payingCar();
                    break;
                case 'n':
                    tb.nopayCar();
                    break;
                default:
                    std::cout << "Unknown key! Press ESC to exit" << std::endl;
            }
        }
    } while (!(key.first && key.second == 27));
    std::cout << tb << std::endl;
    return 0;
}
