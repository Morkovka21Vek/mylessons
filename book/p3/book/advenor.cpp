#include <iostream>

int main() {
	char dir = 'a';
	int x=10, y=10;
	
	while (dir != 'q') 
	{
		std::cout << "Ваши координаты: " << x << ", " << y << std::endl;
		if (x < 5 || x > 15) 
			std::cout << "Осторожно - драконы!" << std::endl; 

		std::cout << "Выберите направление (n,s,e,w): >>> ";
		std::cin >> dir;

		switch(dir) {
			case 'n': y--; break;
			case 's': y++; break;
			case 'e': x++; break;
			case 'w': x--; break;
			case 'q': std::cout << "Выход..." << std::endl; break;
			default: std::cout << "Попробуйте ещё(для выхода введите q)" << std::endl;
		}
	}

	return 0;
}
