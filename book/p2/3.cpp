#include <iostream>

int main() {
    int var = 10;
    std::cout << var << std::endl;

    var += 10;
    std::cout << (var--) << std::endl;

    std::cout << var << std::endl;

    return 0;
}
