#include <iostream>

enum itsaWord {NO, YES};

int main() {
	itsaWord isWord = NO;
	char ch = 'a';
	int wordcount = 0;

	std::cout << ">>> ";
	do {
		ch = getchar();
		if (ch == ' ' || ch == '\n'){
			if (isWord == YES) {
				wordcount ++;
				isWord = NO;
			}
		}
		else {
			if (isWord == NO)
				isWord = YES;
		}
	} while (ch != '\n');
	std::cout << std::endl << "Чисто слов: " << wordcount << "---" << std::endl;
}
