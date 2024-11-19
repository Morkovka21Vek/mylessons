#include <iostream>

int main() {

	int var;
	std::cout << "Input a number please: >>> ";
	std::cin >> var;

	std::cout << "var < 10 is "  << (var < 10)  << std::endl
			  << "var > 10 is "  << (var > 10)  << std::endl
			  << "var == 10 is " << (var == 10) << std::endl;
}
