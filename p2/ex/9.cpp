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
	//std::cout << "x = " << x << "; y = " << y;

	//common_divi = static_cast<int>(y/x);
	//common_divi += !common_divi;
	//x /= common_divi*y;
	//y /= common_divi*y;

    std::cout << "Сумма равна: >>" << x << "/" << y << std::endl;

    return 0;
}
