#include <iostream>

int main() {
	
	char dir = 'a';
	int x=10, y=10;

	std::cout << "Нажмите q для выхода..." << std::endl;
	
	while (dir != 'q') 
	{
		std::cout << "Ваши координаты: " << x << ", " << y << std::endl;
		std::cout << "Выберите направление (n,s,e,w): ";
		
		std::cin >> dir;

		if (dir == 'n') y--;
		else if (dir == 's') y++;
			 else if (dir == 'e') x++;
				  else if (dir == 'w') x--;
	}	

	return 0;
}
