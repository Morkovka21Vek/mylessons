#include <iostream>
#include <iomanip>

int main() {

	int pow = 1, numb = 1;
	while (pow < 10000) 
	{
		std::cout << std::setw(2) << numb
				  << std::setw(5) << pow << std::endl;
		++numb;
		pow = numb*numb*numb*numb;
	}
	
	std::cout << std::endl;
	
	return 0;
}
