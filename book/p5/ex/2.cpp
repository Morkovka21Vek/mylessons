#include <iostream>

double power(double n, int p = 2) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

int main() {
    std::cout << "Введите число и степень через пробел: >> ";

    double n;
    int p;
    std::cin >> n >> p;

    std::cout << power(n, p) << std::endl;

    return 0;
}
