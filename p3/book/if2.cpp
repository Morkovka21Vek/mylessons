#include <iostream>

int main() {

	int x;
	std::cout << "Введите число: >>> ";
	std::cin >> x;
	
	if (x > 100) {
		std::cout << "Число " << x;
		std::cout << " больше, чем 100" << std::endl;
	}
	
	return 0;
}