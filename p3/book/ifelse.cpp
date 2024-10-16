#include <iostream>

int main() {

	int x;
	std::cout << "Введите число: >>> ";
	std::cin >> x;
	
	if (x > 100)
		std::cout << "Это число больше, чем 100" << std::endl;
	else
		std::cout << "Это число не больше, чем 100" << std::endl;
	
	return 0;
}
