#include <iostream>

struct fraction {
  int a;
  int b;
};

int main() {
    int common_divi; // Переменная common_divi нужна для нахождения целого общего делителя у дроби
    char dummychar; // Временная переменная

    fraction frac1, frac2, out;

    std::cout << "Данная программа складывает обычные дроби.\nДроби необходимо вводить в формате: \"x/y\".\nВведите 1-ю дробь: >>> ";
    std::cin >> frac1.a >> dummychar >> frac1.b;
    std::cout << "Введите 2-ю дробь: >>> ";
    std::cin >> frac2.a >> dummychar >> frac2.b;

    out.a = frac1.a*frac2.b + frac1.b*frac2.a;
    out.b = frac1.b*frac2.b;

	int minNum, j;
	do {
		minNum = (out.a < out.b) ? out.a : out.b;
		for	(j = minNum; j > 0; j--) {
			if (!(out.a % j) && !(out.b % j)) {
				out.a /= j;
				out.b /= j;
				break;
			}
		}
	} while (j != 1);

    std::cout << "Сумма равна: >> " << out.a << '/' << out.b << std::endl;

    return 0;
}

