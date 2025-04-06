#include <iostream>
#include <ostream>

class fraction {
    public:
        fraction(): a(0), b(0)
        {}

        fraction(int _a, int _b): a(_a), b(_b)
        {}

        void getData();
        void getValues(int& a, int& b) const;

        fraction operator+(fraction) const;

    private:
        int a;
        int b;
};

void fraction::getData() {
    char space;
    std::cin >> this->a >> space >> this->b;
}

fraction fraction::operator+(fraction other) const {
    int other_a, other_b;
    int out_a, out_b;
    other.getValues(other_a, other_b);

    out_a = this->a*other_b + this->b*other_a;
    out_b = this->b*other_b;

	int minNum, j;
	do {
		minNum = (out_a < out_b) ? out_a : out_b;
		for	(j = minNum; j > 0; j--) {
			if (!(out_a % j) && !(out_b % j)) {
				out_a /= j;
				out_b /= j;
				break;
			}
		}
	} while (j != 1);

    return fraction(out_a, out_b);
}

void fraction::getValues(int& a, int& b) const {
    a = this->a;
    b = this->b;
}

std::ostream& operator<<(std::ostream& os, const fraction& obj) {
    int a, b;
    obj.getValues(a, b);

    os << a << '/' << b;
    return os;
}

int main() {
    fraction frac1, frac2;
    char repeat = 0;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо вводить в формате: \"x/y\"." << std::endl;
    do {
        std::cout << "Введите 1-ю дробь: >>> ";
        frac1.getData();

        std::cout << "Введите 2-ю дробь: >>> ";
        frac2.getData();

        std::cout << "Сумма равна: >> " << frac1 + frac2 << std::endl;

        std::cout << "Хотите продолжить?(y/*)";
        std::cin >> repeat;
    } while(repeat == 'y');

    return 0;
}

