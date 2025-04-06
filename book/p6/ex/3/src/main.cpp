#include "Time.hpp"
#include <iostream>

int main() {
    const Time t1(1, 2, 3), t2(3, 2, 1);
    Time t3 = t1 + t2;

    std::cout << t3 << std::endl;

    return 0;
}
