#include <iostream>
//#include <curses.h>
#include <unistd.h>

int main() {

	int chcount = 0, wdcount = 1;
	char ch = 'a';

	std::cout << "Введите строку: >>> ";
	
	while (ch != '\n') {

		ch = getchar();
		//read(STDIN_FILENO, &ch, 1);
		//std::cout << ch;

		if (ch == ' ') wdcount++;
		else chcount++;
	}
	
	std::cout << "Слов: " << wdcount << std::endl
			  << "Букв: "   << (chcount-1) << std::endl;

	return 0;
}
