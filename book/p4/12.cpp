#include <cstdlib>
#include <iostream>

struct fraction {
    int a;
    int b;
};

void reduction(int &x, int &y) {
    int j;
    do {
        if (x == 0) {
            y = 0;
            break;
        }
        int minNum = (x < y) ? x : y;
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
    fraction a;
    fraction b;
    fraction out;
    char dummychar;
    char op;
    char contin;

    std::cout << "Данная программа производит операции(+-*/) обычные "
                 "дроби.\nДроби необходимо вводить в формате: \"x/y\"."
              << std::endl;

    do {
        std::cout << "Введите 1-ю дробь, опреранд и 2-ю дробь: \n>>> ";
        std::cin >> a.a >> dummychar >> a.b >> op >> b.a >> dummychar >> b.b;

        switch (op) {
        case '+':
            out.a = a.a * b.b + a.b * b.a;
            out.b = a.b * b.b;
            break;

        case '-':
            out.a = a.a * b.b - a.b * b.a;
            out.b = a.b * b.b;
            break;

        case '*':
            out.a = a.a * b.a;
            out.b = a.b * b.b;
            break;

        case '/':
            out.a = a.a * b.b;
            out.b = a.b * b.a;
            break;

        default:
            std::cout << "Введён неправильный операнд!" << std::endl;
            std::exit(1);
        }

        reduction(out.a, out.b);

        switch (op) {
        case '+':
            std::cout << "Сумма равна: >> " << out.a << "/" << out.b
                      << std::endl;
            break;
        case '-':
            std::cout << "Разность равна: >> " << out.a << "/" << out.b
                      << std::endl;
            break;
        case '*':
            std::cout << "Произведение равно: >> " << out.a << "/" << out.b
                      << std::endl;
            break;
        case '/':
            std::cout << "Частное равно: >> " << out.a << "/" << out.b
                      << std::endl;
            break;
        default:
            std::cout << "Введён неправильный операнд!" << std::endl;
            std::exit(1);
        }

        std::cout << "Ешё раз? (Y/n): ";
        std::cin >> contin;
    } while (contin != 'n');

    return 0;
}
