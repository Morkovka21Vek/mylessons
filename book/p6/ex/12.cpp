#include <iostream>
#include <iomanip>
#include <ostream>

class fraction {
    public:
        fraction(): a(0), b(0)
        {}

        fraction(int _a, int _b);

        void getData();
        void getValues(int& a, int& b) const;

        fraction operator+(fraction) const;
        fraction operator-(fraction) const;
        fraction operator*(fraction) const;
        fraction operator/(fraction) const;

    private:
        void reducing();
        int a;
        int b;
};

fraction::fraction(int _a, int _b): a(_a), b(_b)
{
    reducing();
}

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

void fraction::reducing() {
    int minNum, j;
    do {
        minNum = (this->a < this->b) ? this->a : this->b;
        for    (j = minNum; j > 0; j--) {
            if (!(this->a % j) && !(this->b % j)) {
                this->a /= j;
                this->b /= j;
                break;
            }
        }
    } while (j != 1);
}

fraction fraction::operator+(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b + this->b*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reducing();

    return out;
}

fraction fraction::operator-(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b - this->b*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reducing();

    return out;
}

fraction fraction::operator*(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_a;
    int out_b = this->b*other_b;

    fraction out(out_a, out_b);
    out.reducing();

    return out;
}

fraction fraction::operator/(fraction other) const {
    int other_a, other_b;
    other.getValues(other_a, other_b);

    int out_a = this->a*other_b;
    int out_b = this->b*other_a;

    fraction out(out_a, out_b);
    out.reducing();

    return out;
}

void fraction::getValues(int& a, int& b) const {
    a = this->a;
    b = this->b;
}

std::ostream& operator<<(std::ostream& os, const fraction& obj) {
    int a, b;
    obj.getValues(a, b);

    std::ostringstream tmp;
    tmp << a << '/' << b;

    os << tmp.str();

    return os;
}

int main() {
    int denominator;
    size_t width = 3;

    std::cout << "Введите знаменатель для создания таблицы умножения: "; std::cin >> denominator;

    if (denominator <= 0) {
        std::cout << "Некорректный знаменатель!";
        goto ERROR;
    }

    do {
        int temp_denominator = denominator * denominator;
        while(temp_denominator >= 10)
        {
            temp_denominator /= 10;
            width += 2;
        }
    } while(0);

    std::cout << std::left << std::setfill(' ');

    std::cout << "┌";
    for (int num = 0; num < denominator+1; num++) {
        for (int num2 = 0; num2 < width; num2++)
            std::cout << "─";
        if(num != denominator)
            std::cout << "┬";
    }
    std::cout << "┐" << std::endl;

    for (int i = 0; i <= denominator; i++) {
        std::cout << "│";
        for (int j = 0; j <= denominator; j++) {
            if (i == 0 && j != 0)
                std::cout << "\033[44m" << std::setw(width) << fraction(j, denominator) << std::setw(0) << "\033[0m│";
            else if (i != 0 && j == 0)
                std::cout << "\033[46m" << std::setw(width) << fraction(i, denominator) << std::setw(0) << "\033[0m│";
            else if (i == 0 && j == 0)
                std::cout << "\033[43m" << std::setw(width) << "j/i" << std::setw(0) << "\033[0m│";
            else
            {
                std::cout << std::setw(width) << fraction(j, denominator) * fraction(i, denominator) << std::setw(0) << "│";
            }
        }
        if (i != denominator) {
            std::cout << std::endl << "├";
            for (int num = 0; num < denominator+1; num++) {
                for (int num2 = 0; num2 < width; num2++)
                    std::cout << "─";
                if(num != denominator)
                    std::cout << "┼";
            }

            std::cout << "┤" << std::endl;
        }
    }

    std::cout << std::endl << "└";
    for (int num = 0; num < denominator+1; num++) {
        for (int num2 = 0; num2 < width; num2++)
            std::cout << "─";
        if(num != denominator)
            std::cout << "┴";
    }
    std::cout << "┘" << std::endl;

    return 0;
ERROR:
    return 1;
}
