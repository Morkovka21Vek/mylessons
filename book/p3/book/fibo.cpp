#include <iostream>

int main() {
	
	const unsigned long limit = 4294967295;

	unsigned long next = 0;
	unsigned long last = 1;
	
	while (next < limit / 2)
	{
		std::cout << last << "   ";

		long sum = next + last;
		next = last;
		last = sum;
	}

	std::cout << std::endl;

	return 0;
}
