#include <iostream>
#include <ostream>

class fraction {
  public:
    fraction() = default;
    fraction(int a, int b);

    fraction &operator+=(fraction obj);
    fraction &operator/=(int div);

  private:
    friend std::ostream &operator<<(std::ostream &os, const fraction &obj);
    friend std::istream &operator>>(std::istream &in, fraction &d);

    void reduce();
    static int computeGCD(int, int);
    int a = 0;
    int b = 0;
};

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
    return (_a == 0) ? 1 : _a;
}

fraction &fraction::operator+=(fraction obj) {
    this->a = this->a * obj.b + this->b * obj.a;
    this->b = this->b * obj.b;
    reduce();
    return *this;
}

fraction &fraction::operator/=(int div) {
    this->b *= div;
    reduce();
    return *this;
}

std::ostream &operator<<(std::ostream &os, const fraction &obj) {
    if (obj.b > 1)
        os << obj.a << '/' << obj.b;
    else
        os << obj.a;
    return os;
}

std::istream &operator>>(std::istream &in, fraction &obj) {
    char temp;
    in >> obj.a >> temp >> obj.b;
    obj.reduce();

    return in;
}

int main() {
    const size_t BUFFSIZE = 100;
    fraction frac[BUFFSIZE];

    size_t buff_pos = 0;

    std::cout << "Вводите дроби в формате \"a/b\". Для выхода нажмите Ctrl+D"
              << std::endl;
    do {
        std::cout << ">> " << std::flush;
        if (std::cin >> frac[buff_pos++])
            continue;

        buff_pos--;
        break;
    } while (buff_pos < BUFFSIZE);

    fraction sum(0, 1);
    for (size_t i = 0; i < buff_pos; i++) {
        sum += frac[i];
    }
    sum /= buff_pos;

    std::cout << "\nСреднее значение: " << sum << std::endl;

    return 0;
}
