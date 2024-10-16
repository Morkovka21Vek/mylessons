#include <iostream>

int main() {

	long dividend, divisor;
	char ch;

	do {
		std::cout << "Введите делимое: >>> "; std::cin >> dividend;
		std::cout << "Введите делитель: >>> "; std::cin >> divisor;

		if (divisor == 0) {
			std::cout << "Некорректный делитель!" << std::endl;
			continue;
		}

		std::cout << dividend << "/" << divisor << " = " << dividend/divisor << " (ост. " << dividend % divisor << " )" << std::endl
				  << "Ещё раз? (Y/n): ";

		std::cin >> ch;
	} while (ch != 'n');

	return 0;
}
