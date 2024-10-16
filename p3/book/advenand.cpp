#include <iostream>
#include <cstdlib>

int main() {
	char dir = 'a';
	int x=10, y=10;
	
	while (dir != 'q') 
	{
		std::cout << "Ваши координаты: " << x << ", " << y << std::endl;

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
		
		if (!(x%7) && !(y%7))
			std::cout << "Вы нашли гриб!" << std::endl;

		if (x == 7 && y == 11)
		{
			std::cout << "Вы нашли сокровище!" << std::endl;
			exit(0);
		}

	}
	return 0;
}
