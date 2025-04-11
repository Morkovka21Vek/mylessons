#include <iostream>
#include <cstdlib>

struct fraction {
  int a;
  int b;
};

fraction fadd(fraction a, fraction b) {
    fraction out;

    out.a = a.a * b.b + a.b * b.a;
    out.b = a.b * b.b;

    return out;
}

fraction fsub(fraction a, fraction b) {
    fraction out;

    out.a = a.a * b.b - a.b * b.a;
    out.b = a.b * b.b;

    return out;
}

fraction fmul(fraction a, fraction b) {
    fraction out;

    out.a = a.a * b.a;
    out.b = a.b * b.b;

    return out;
}

fraction fdiv(fraction a, fraction b) {
    fraction out;

    out.a = a.a * b.b;
    out.b = a.b * b.a;

    return out;
}

int main() {
    int common_divi; // Переменная common_divi нужна для нахождения целого общего делителя у дроби
    fraction a, b, out;
    char dummychar, op, contin;

    std::cout << "Данная программа производит операции(+-*/) над обычными дробями.\nДроби необходимо вводить в формате: \"x/y\"." << std::endl;

    do
    {
        std::cout << "Введите 1-ю дробь, опреранд и 2-ю дробь: \n>>> ";
        std::cin >> a.a >> dummychar >> a.b >> op >> b.a >> dummychar >> b.b;

        switch (op){
            case '+': out = fadd(a, b); break;
            case '-': out = fsub(a, b); break;
            case '*': out = fmul(a, b); break;
            case '/': out = fdiv(a, b); break;
            default:
                std::cout << "Введён неправильный операнд!" << std::endl;
                goto ERROR;
        }


        int minNum, j;
        do {
            if (out.a == 0) {
                out.b = 0;
                break;
            }
            minNum = (out.a < out.b) ? out.a : out.b;
            for (j = minNum; j > 0; j--) {
                if (!(out.a % j) && !(out.b % j)) {
                    out.a /= j;
                    out.b /= j;
                    break;
                }
            }
        } while (j != 1);

        switch (op) {
            case '+':
                std::cout << "Сумма равна: >> " << out.a << "/" << out.b << std::endl;
                break;
            case '-':
                std::cout << "Разность равна: >> " << out.a << "/" << out.b << std::endl;
                break;
            case '*':
                std::cout << "Произведение равно: >> " << out.a << "/" << out.b << std::endl;
                break;
            case '/':
                std::cout << "Частное равно: >> " << out.a << "/" << out.b << std::endl;
                break;
        }

        std::cout << "Ешё раз? (Y/n): ";
        std::cin >> contin;
    } while (contin != 'n');

    return 0;
ERROR:
    return 1;
}
