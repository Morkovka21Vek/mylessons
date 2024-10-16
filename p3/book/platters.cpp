#include <iostream>

int main() {

	int speed;

	std::cout << "Введите число 33, 45 или 78:\n>>> ";
	std::cin >> speed;

	switch(speed) 
	{
		case 33:
			std::cout << "Долгоиграющий формат" << std::endl;
			break;
		case 45:
			std::cout << "Формат сигнала" << std::endl;
			break;
		case 78:
			std::cout << "Устаревший формат" << std::endl;
			break;
	}

	return 0;
}
