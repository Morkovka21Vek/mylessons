#include <iostream>

int main() {

	int a, b, c;
	std::cout << "Введите числа a, b, c" << std::endl;
	std::cin >> a >> b >> c;
	
	if (a == b)
		if (b == c)
			std::cout << "a, b, c равны" << std::endl;
		else
			std::cout << "b, c не равны" << std::endl;
	
	std::cout << "-----------------------------" << std::endl;

	if (a == b){
		if (b == c)
			std::cout << "a, b, c равны" << std::endl;
	} else
		std::cout << "a и b не равны" << std::endl;

}
