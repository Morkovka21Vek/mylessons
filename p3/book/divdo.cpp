#include <iostream>

int main() {

	long dividend, divisor;
	char ch;

	do {
		// Прикольный баг если тут ввести букву
		std::cout << "Введите делимое: >>> ";  std::cin >> dividend;
		std::cout << "Введите делитель: >>> "; std::cin >> divisor;

		std::cout << "Частное равно "   << dividend / divisor
				  << ", остаток равен " << dividend % divisor;

		std::cout << std::endl << "Ещё раз?(Y/n): ";
		std::cin >> ch;
	} while (ch != 'n');

	return 0;
}
