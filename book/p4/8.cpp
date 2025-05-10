#include <iostream>

struct fraction {
    int a;
    int b;
};

void reduction(int &x, int &y) {
    int minNum;
    int j;
    do {
        if (x == 0) {
            y = 0;
            break;
        }
        minNum = (x < y) ? x : y;
        for (j = minNum; j > 0; j--) {
            if (!(x % j) && !(y % j)) {
                x /= j;
                y /= j;
                break;
            }
        }
    } while (j != 1);
}

int main() {
    char dummychar;
    fraction frac1;
    fraction frac2;
    fraction out;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо "
                 "вводить в формате: \"x/y\".\nВведите 1-ю дробь: >>> ";
    std::cin >> frac1.a >> dummychar >> frac1.b;
    std::cout << "Введите 2-ю дробь: >>> ";
    std::cin >> frac2.a >> dummychar >> frac2.b;

    out.a = frac1.a * frac2.b + frac1.b * frac2.a;
    out.b = frac1.b * frac2.b;

    reduction(out.a, out.b);

    std::cout << "Сумма равна: >> " << out.a << '/' << out.b << std::endl;

    return 0;
}
