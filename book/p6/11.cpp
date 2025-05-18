#include <iostream>
#include <ostream>

class fraction {
    public:
        fraction();
        fraction(int a, int b);

        void getData();
        void getValues(int& a, int& b) const;

        fraction operator+(fraction) const;
        fraction operator-(fraction) const;
        fraction operator*(fraction) const;
        fraction operator/(fraction) const;

    private:
        void reduce();
        int computeGCD(int, int) const;
        int a;
        int b;
};

fraction::fraction(): a(0), b(0)
{}

fraction::fraction(int _a, int _b): a(_a), b(_b)
{}

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

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

int fraction::computeGCD(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

fraction fraction::operator+(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b + this->b*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reduce();

    return out;
}

fraction fraction::operator-(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b - this->b*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reduce();

    return out;
}

fraction fraction::operator*(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reduce();

    return out;
}

fraction fraction::operator/(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b;
    int out_b = this->b*other_a;

    fraction out(out_a, out_b);
    out.reduce();

    return out;
}

void fraction::getValues(int& a, int& b) const {
    a = this->a;
    b = this->b;
}

std::ostream& operator<<(std::ostream& os, const fraction& obj) {
    int a, b;
    obj.getValues(a, b);

    if (b != 1)
        os << a << '/' << b;
    else
        os << a;
    return os;
}

int main() {
    char op, contin;
    fraction frac1, frac2;

    std::cout << "Данная программа производит операции(+-*/) обычные дроби.\nДроби необходимо вводить в формате: \"x/y\"." << std::endl;

    do {
        std::cout << "Введите 1-ю дробь: "; frac1.getData();
        std::cout << "опреранд: "; std::cin >> op;
        std::cout << "и 2-ю дробь: "; frac2.getData();

        switch (op) {
            case '+':
                std::cout << "Сумма равна: >> " << frac1 + frac2 << std::endl;
                break;
            case '-':
                std::cout << "Разность равна: >> " << frac1 - frac2 << std::endl;
                break;
            case '*':
                std::cout << "Произведение равно: >> " << frac1 * frac2 << std::endl;
                break;
            case '/':
                std::cout << "Частное равно: >> " << frac1 / frac2 << std::endl;
                break;
            default:
                std::cout << "Введён неправильный операнд!" << std::endl;
        }

        std::cout << "Ешё раз? (Y/n): ";
        std::cin >> contin;
    } while (contin != 'n');

    return 0;
}
