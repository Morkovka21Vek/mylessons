#include <iostream>

int main() {

	for (int j = 0; j < 80; j++) 
		std::cout << ((j%8) ? ' ' : 'X');

	std::cout << std::endl;

	return 0;
}
