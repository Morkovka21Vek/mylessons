#include <iostream>

int main() {
	int chcount = 0, wdcount = 1;
	char ch;
	
	while ((ch = getchar()) != '\n') {

		if (ch == ' ') wdcount++;
		else chcount++;
	}
	
	std::cout << std::endl << "Слов: " << wdcount << std::endl
			  			   << "Букв: " << chcount << std::endl;

	return 0;
}
