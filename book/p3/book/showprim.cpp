#include <iostream>

int main() {
	const unsigned char WHITE = '@';
	const unsigned char GRAY = '-';

	unsigned char ch;

	for (int count = 0; count < 80*25-1; count++) {

		ch = WHITE;

		for (int j = 2; j < count; j++)
			if (count % j == 0) {
				ch = GRAY;
				break;
			}

		std::cout << ch;
		if (count % 80 == 0) std::cout << std::endl;
	}

	std::cin;
	return 0;
}
