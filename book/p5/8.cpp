#include <iostream>

void swap(int &a, int &b) {
    int temp;

    temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 1;
    int b = 2;
    std::cout << "a = " << a << "; b = " << b << std::endl;

    std::cout << "Swapping..." << std::endl;
    swap(a, b);

    std::cout << "a = " << a << "; b = " << b << std::endl;

    return 0;
}
