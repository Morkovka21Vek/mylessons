#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

class Fraction {
  public:
    Fraction() : a(0), b(0) {}

    Fraction(int _a, int _b, bool is_reduce = true);

    void setData();
    friend Fraction operator*(const Fraction &, const Fraction &);
    friend std::ostream &operator<<(std::ostream &os, const Fraction &obj);

  private:
    void reduce();
    static int computeGCD(int, int);
    int a;
    int b;
};

Fraction::Fraction(int _a, int _b, bool is_reduce) : a(_a), b(_b) {
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

int Fraction::computeGCD(int _a, int _b) {
    while (_b != 0) {
        int temp = _b;
        _b = _a % _b;
        _a = temp;
    }
    return _a;
}

Fraction operator*(const Fraction &obj1, const Fraction &obj2) {
    return Fraction(obj1.a * obj2.a, obj1.b * obj2.b, true);
}

std::ostream &operator<<(std::ostream &os, const Fraction &obj) {
    std::ostringstream tmp;
    if (obj.b == 1)
        tmp << obj.a;
    else
        tmp << obj.a << '/' << obj.b;

    return os << tmp.str();
}

size_t getWidth(int denominator) {
    size_t width = 3;

    int temp_denominator = denominator * denominator;
    while (temp_denominator >= 10) {
        temp_denominator /= 10;
        width += 2;
    }

    return width;
}

void printHorizontalLine(int denominator, size_t width, const std::string &left,
                         const std::string &middle, const std::string &right) {
    std::cout << left;
    for (int i = 0; i <= denominator; i++) {
        for (int j = 0; j < width; j++)
            std::cout << "─";
        std::cout << (i != denominator ? middle : right);
    }
    std::cout << std::endl;
}

Fraction getCellContent(int x, int y, int denominator) {
    if (y == 0 && x != 0)
        return Fraction(x, denominator, false);
    if (y != 0 && x == 0)
        return Fraction(y, denominator, false);
    if (y == 0 && x == 0)
        return Fraction(0, 0, false);
    return Fraction(x, denominator) * Fraction(y, denominator);
}

void draw(int denominator, size_t width) {
    std::cout << std::left << std::setfill(' ');

    printHorizontalLine(denominator, width, "┌", "┬", "┐");

    for (int y = 0; y <= denominator; y++) {
        std::cout << "│";
        for (int x = 0; x <= denominator; x++) {
            std::cout << std::setw(width) << getCellContent(x, y, denominator);
            std::cout << "│";
        }

        std::cout << std::endl;
        if (y != denominator)
            printHorizontalLine(denominator, width, "├", "┼", "┤");
        else
            printHorizontalLine(denominator, width, "└", "┴", "┘");
    }
}

int main() {
    int denominator;

    std::cout << "Введите знаменатель для создания таблицы умножения: ";
    std::cin >> denominator;
    if (denominator <= 0) {
        std::cout << "Некорректный знаменатель!" << std::endl;
        return 1;
    }

    size_t width = getWidth(denominator);
    draw(denominator, width);

    return 0;
}
