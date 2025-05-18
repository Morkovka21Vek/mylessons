#include <iostream>
#include <ostream>

class fraction {
    public:
        fraction();
        fraction(int a, int b);

        void getData();
        void getValues(int& a, int& b) const;

        fraction operator+(fraction) const;

    private:
        void reduce();
        int computeGCD(int, int) const;

        int a;
        int b;
};

fraction::fraction(): a(0), b(0)
{}

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

int fraction::computeGCD(int _a, int _b) const {
    while (_b != 0) {
        int temp = _b;
        _b = _a % _b;
        _a = temp;
    }
    return _a;
}

fraction::fraction(int _a, int _b): a(_a), b(_b)
{
    reduce();
}

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

fraction fraction::operator+(fraction other) const {
    return fraction(this->a*other.b + this->b*other.a, this->b*other.b);
}

void fraction::getValues(int& _a, int& _b) const {
    _a = this->a;
    _b = this->b;
}

std::ostream& operator<<(std::ostream& os, const fraction& obj) {
    int a;
    int b;
    obj.getValues(a, b);

    os << a << '/' << b;
    return os;
}

int main() {
    fraction frac1;
    fraction frac2;
    char repeat = 0;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо вводить в формате: \"x/y\"." << std::endl;
    do {
        std::cout << "Введите 1-ю дробь: >>> ";
        frac1.getData();

        std::cout << "Введите 2-ю дробь: >>> ";
        frac2.getData();

        std::cout << "Сумма равна: >> " << frac1 + frac2 << std::endl;

        std::cout << "Хотите продолжить?(y/*) ";
        std::cin >> repeat;
    } while(repeat == 'y');

    return 0;
}

