#include "Time.hpp"
#include <iostream>

int main() {
    {
        const Time t1(1, 2, 3);
        const Time t2(3, 2, 1);
        std::cout << t1 << " + " << t2 << " = " << t1 + t2 << std::endl;
    }

    {
        Time t1(1, 0, 59);
        Time t2(3, 1, 61);
        std::cout << t1 << " + " << t2 << " = " << t1 + t2 << std::endl;
        t1++;
        ++t2;
        std::cout << t1 << ' ' << t2 << std::endl;
    }

    {
        const Time t1(1, 4000000180, 400000072);
        std::cout << t1 << std::endl;
    }

    return 0;
}
