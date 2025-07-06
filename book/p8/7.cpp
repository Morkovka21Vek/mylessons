#include <iostream>
#include <ostream>

class fraction {
  public:
    fraction() = default;
    fraction(int a, int b);
    void getData();

  private:

    friend fraction operator+(fraction obj1, fraction obj2);
    friend fraction operator-(fraction obj1, fraction obj2);
    friend fraction operator*(fraction obj1, fraction obj2);
    friend fraction operator/(fraction obj1, fraction obj2);
    friend bool operator==(fraction obj1, fraction obj2);
    friend bool operator!=(fraction obj1, fraction obj2);
    friend std::ostream &operator<<(std::ostream &os, const fraction &obj);

    void reduce();
    static int computeGCD(int, int);
    int a = 0;
    int b = 0;
};

fraction::fraction(int a, int b) : a(a), b(b) { reduce(); }

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

void fraction::reduce() { int numerator = this->a;
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

fraction operator+(fraction obj1, fraction obj2) {
    return fraction(obj1.a * obj2.b + obj1.b * obj2.a, obj1.b * obj2.b);
}

fraction operator-(fraction obj1, fraction obj2) {
    return fraction(obj1.a * obj2.b - obj1.b * obj2.a, obj1.b * obj2.b);
}

fraction operator*(fraction obj1, fraction obj2) {
    return fraction(obj1.a * obj2.a, obj1.b * obj2.b);
}

fraction operator/(fraction obj1, fraction obj2) {
    return fraction(obj1.a * obj2.b, obj1.b * obj2.a);
}

bool operator==(fraction obj1, fraction obj2) {
    obj1.reduce();
    obj2.reduce();
    return obj1.a == obj2.a && obj1.b == obj2.b;
}
bool operator!=(fraction obj1, fraction obj2) {
    obj1.reduce();
    obj2.reduce();
    return !(obj1.a == obj2.a && obj1.b == obj2.b);
}

std::ostream &operator<<(std::ostream &os, const fraction &obj) {
    if (obj.b > 1)
        os << obj.a << '/' << obj.b;
    else
        os << obj.a;
    return os;
}

int main() {
    char op;
    fraction frac1;
    fraction frac2;

    std::cout << "Данная программа производит операции(+-*/) обычные "
                 "дроби.\nДроби необходимо вводить в формате: \"x/y\".(Для выхода введите дробь \"0/1\")"
              << std::endl;

    while(true) {
        std::cout << "Введите 1-ю дробь: ";
        frac1.getData();
        if(frac1 == fraction(0, 1))
            break;
        std::cout << "опреранд: ";
        std::cin >> op;
        std::cout << "и 2-ю дробь: ";
        frac2.getData();
        if(frac2 == fraction(0, 1))
            break;

        switch (op) {
        case '+':
            std::cout << "Сумма равна: >> " << frac1 + frac2 << std::endl;
            break;
        case '-':
            std::cout << "Разность равна: >> " << frac1 - frac2 << std::endl;
            break;
        case '*':
            std::cout << "Произведение равно: >> " << frac1 * frac2
                      << std::endl;
            break;
        case '/':
            std::cout << "Частное равно: >> " << frac1 / frac2 << std::endl;
            break;
        default:
            std::cout << "Введён неправильный операнд!" << std::endl;
        }
    }

    return 0;
}
