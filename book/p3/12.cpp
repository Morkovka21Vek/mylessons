/*
 * Создайте калькулятор, выполняющий четыре арифметических действия над дробями
 * (см. упражнение 9 главы 2 и упражнение 4 этой главы). Формулы,
 * демонстрирующие выполнение арифметических операций над дробями, приведены
 * ниже. Сложение: a/b+c/d=(a*d+b*c)/(b*d) Вычитание: a/b-c/d=(a*d-b*c)/(b*d)
 * Умножение: a/b*c/d=(a*c)/(b*d)
 * Деление: a/b/c/d = (a*d)/(b*c)
 * Пользователь должен сначала ввести первый операнд, затем знак операции и
 * второй операнд. После вычисления результата программа должна отобразить его
 * на экране и запросить пользователя о его желании произвести еще одну
 * операцию.
 */

#include <cstdlib>
#include <iostream>

void reduction(int x, int y) {
    int minNum, j;
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
    char op;
    char contin;

    std::cout << "Данная программа производит операции(+-*/) обычные "
                 "дроби.\nДроби необходимо вводить в формате: \"x/y\"."
              << std::endl;
    do {
        std::cout << "Введите 1-ю дробь, опреранд и 2-ю дробь: \n>>> ";
        std::cin >> a >> dummychar >> b >> op >> c >> dummychar >> d;

        switch (op) {
        case '+':
            x = a * d + b * c;
            y = b * d;
            break;
        case '-':
            x = a * d - b * c;
            y = b * d;
            break;
        case '*':
            x = a * c;
            y = b * d;
            break;
        case '/':
            x = a * d;
            y = b * c;
            break;
        default:
            std::cout << "Введён неправильный операнд!" << std::endl;
            std::exit(1);
        }

        reduction(x, y);

        switch (op) {
        case '+':
            std::cout << "Сумма равна: >> " << x << "/" << y << std::endl;
            break;
        case '-':
            std::cout << "Разность равна: >> " << x << "/" << y << std::endl;
            break;
        case '*':
            std::cout << "Произведение равно: >> " << x << "/" << y
                      << std::endl;
            break;
        case '/':
            std::cout << "Частное равно: >> " << x << "/" << y << std::endl;
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
