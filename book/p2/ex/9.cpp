#include <iostream>

int main() {
    int a, b, c, d, x, y, common_divi; // Переменная common_divi нужна для нахождения целого общего делителя у дроби
    char dummychar; // Временная переменная

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо вводить в формате: \"x/y\".\nВведите 1-ю дробь: >>> ";
    std::cin >> a >> dummychar >> b;
    std::cout << "Введите 2-ю дробь: >>> ";
    std::cin >> c >> dummychar >> d;

    x = a*d + b*c;
    y = b*d;

	int minNum, j;
	do {
		minNum = (x < y) ? x : y;
		for	(j = minNum; j > 0; j--) {
			if (!(x % j) && !(y % j)) {
				x /= j;
				y /= j;
				break;
			}
		}
	} while (j != 1);

    std::cout << "Сумма равна: >> " << x << "/" << y << std::endl;

    return 0;
}
