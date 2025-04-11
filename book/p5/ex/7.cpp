#include <iostream>

double power(double n, int p = 2);
double power(char   n, int p = 2);
double power(int    n, int p = 2);
double power(long   n, int p = 2);
double power(float  n, int p = 2);

int main() {
    std::cout << "Введите число и степень через пробел: >> ";

    double n;
    int p;
    std::cin >> n >> p;

    std::cout << "double: " << power(n, p)        << std::endl;
    std::cout << "char: "   << power((char)n, p)  << std::endl;
    std::cout << "int: "    << power((int)n, p)   << std::endl;
    std::cout << "long: "   << power((long)n, p)  << std::endl;
    std::cout << "float: "  << power((float)n, p) << std::endl;

    return 0;
}


double power(double n, int p) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

double power(char n, int p) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

double power(int n, int p) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

double power(long n, int p) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}

double power(float n, int p) {
    double result = 1;
    for (int i = 0; i < p; i++) {
        result *= n;
    }
    return result;
}
