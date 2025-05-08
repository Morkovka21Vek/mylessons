#include <iostream>

void zeroSmaller(int &a, int &b) {
    if (a < b)
        a = 0;
    else if (a > b)
        b = 0;
}

int main() {
    int a;
    int b;

    a = 5;
    b = 6;
    zeroSmaller(a, b);
    if (a != 0 || b != 6)
        goto ERROR;

    a = 7;
    b = 4;
    zeroSmaller(a, b);
    if (a != 7 || b != 0)
        goto ERROR;

    a = 5;
    b = 5;
    zeroSmaller(a, b);
    if (a != 5 || b != 5)
        goto ERROR;

    std::cout << "All test passed" << std::endl;
    return 0;

ERROR:
    std::cerr << "TEST ERROR" << std::endl;
    return 1;
}
