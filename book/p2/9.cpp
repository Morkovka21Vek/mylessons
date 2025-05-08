#include <iostream>

void reduction(int& x, int& y) {
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
    int a;
    int b;
    int c;
    int d;
    int x;
    int y;
    char dummychar;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо "
                 "вводить в формате: \"x/y\".\nВведите 1-ю дробь: >>> ";
    std::cin >> a >> dummychar >> b;
    std::cout << "Введите 2-ю дробь: >>> ";
    std::cin >> c >> dummychar >> d;

    x = a * d + b * c;
    y = b * d;

    reduction(x, y);

    std::cout << "Сумма равна: >> " << x << "/" << y << std::endl;

    return 0;
}
