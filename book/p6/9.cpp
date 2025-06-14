#include <iostream>
#include <ostream>

class fraction {
  public:
    fraction();
    fraction(int a, int b);
    void getData();

    friend fraction operator+(const fraction &, const fraction &);
    friend std::ostream &operator<<(std::ostream &os, const fraction &obj);

  private:
    void reduce();
    static int computeGCD(int, int);

    int a;
    int b;
};

fraction::fraction() : a(0), b(0) {}
fraction::fraction(int a, int b) : a(a), b(b) { reduce(); }

void fraction::reduce() {
    int numerator = this->a;
    int denominator = this->b;

    int gcd = computeGCD(abs(numerator), abs(denominator));

    this->a = numerator / gcd;
    this->b = denominator / gcd;

    if (this->b < 0) {
        this->a = -this->a;
        this->b = -this->b;
    }
}

int fraction::computeGCD(int _a, int _b) {
    while (_b != 0) {
        int temp = _b;
        _b = _a % _b;
        _a = temp;
    }
    return _a;
}

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

fraction operator+(const fraction &obj1, const fraction &obj2) {
    return fraction(obj1.a * obj2.b + obj1.b * obj2.a, obj1.b * obj2.b);
}

std::ostream &operator<<(std::ostream &os, const fraction &obj) {
    return os << obj.a << '/' << obj.b;
}

int main() {
    fraction frac1;
    fraction frac2;
    char repeat = 0;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо "
                 "вводить в формате: \"x/y\"."
              << std::endl;
    do {
        std::cout << "Введите 1-ю дробь: >>> ";
        frac1.getData();

        std::cout << "Введите 2-ю дробь: >>> ";
        frac2.getData();

        std::cout << "Сумма равна: >> " << frac1 + frac2 << std::endl;

        std::cout << "Хотите продолжить?(y/*) ";
        std::cin >> repeat;
    } while (repeat == 'y');

    return 0;
}
