#include <iostream>
// Не работает импорт <process.h>
#include <cstdlib>

int main() {

	unsigned long n, j;
	std::cout << "Введите число: >>> ";
	std::cin >> n;

	for (j = 2; j <= n/2; j++)
		if(n % j == 0) {
			std::cout << "Число не простое, оно делится на " << j << std::endl;
			exit(0);
		}

	std::cout << "Число " << n << " - простое." << std::endl;

	return 0;
}
