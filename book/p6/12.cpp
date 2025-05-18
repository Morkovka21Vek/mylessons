#include <iostream>
#include <iomanip>
#include <ostream>
#include <string>

class Fraction {
    public:
        Fraction(): a(0), b(0)
        {}

        Fraction(int _a, int _b, bool is_reduce = true);

        void setData();
        void getValues(int& a, int& b) const;

        Fraction operator*(Fraction) const;

    private:
        void reduce();
        int computeGCD(int, int) const;
        int a;
        int b;
};

Fraction::Fraction(int _a, int _b, bool is_reduce): a(_a), b(_b)
{
    if (is_reduce)
        reduce();
}

void Fraction::reduce() {
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

int Fraction::computeGCD(int a, int b) const {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

Fraction Fraction::operator*(Fraction other) const {
    Fraction out(this->a*other.a, this->b*other.b, true);

    return out;
}

void Fraction::getValues(int& a, int& b) const {
    a = this->a;
    b = this->b;
}

std::ostream& operator<<(std::ostream& os, const Fraction& obj) {
    int a, b;
    obj.getValues(a, b);

    std::ostringstream tmp;
    if (b == 1)
        tmp << a;
    else
        tmp << a << '/' << b;

    return os << tmp.str();
}

size_t getWidth(int denominator) {
    size_t width = 3;

    int temp_denominator = denominator * denominator;
    while(temp_denominator >= 10)
    {
        temp_denominator /= 10;
        width += 2;
    }

    return width;
}

void printHorizontalLine(int denominator, size_t width, std::string left, std::string middle, std::string right) {
    std::cout << left;
    for (int i = 0; i <= denominator; i++) {
        for (int j = 0; j < width; j++)
            std::cout << "─";
        std::cout << (i != denominator ? middle : right);
    }
    std::cout << std::endl;
}

int main() {
    int denominator;

    std::cout << "Введите знаменатель для создания таблицы умножения: "; std::cin >> denominator;
    if (denominator <= 0) {
        std::cout << "Некорректный знаменатель!" << std::endl;
        return 1;
    }

    size_t width = getWidth(denominator);

    std::cout << std::left << std::setfill(' ');

    printHorizontalLine(denominator, width, "┌", "┬", "┐");

    for (int y = 0; y <= denominator; y++) {
        std::cout << "│";
        for (int x = 0; x <= denominator; x++) {
            if (y == 0 && x != 0)
                std::cout << std::setw(width) << Fraction(x, denominator, false);
            else if (y != 0 && x == 0)
                std::cout << std::setw(width) << Fraction(y, denominator, false);
            else if (y == 0 && x == 0)
                std::cout << std::setw(width) << "";
            else
                std::cout << std::setw(width) << Fraction(x, denominator) * Fraction(y, denominator);
            std::cout << "│";
        }

        std::cout << std::endl;
        if (y != denominator)
            printHorizontalLine(denominator, width, "├", "┼", "┤");
        else
            printHorizontalLine(denominator, width, "└", "┴", "┘");
    }

    return 0;
}
