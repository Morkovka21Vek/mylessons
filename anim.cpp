#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
//#include <ncurses.h>
//#include <string.h> 

int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono; // nanoseconds, system_clock, seconds

	int screenX = 185, screenY = 45; // Размеры "экрана"
	char ch;
	int posX=3, posY=3, speedX=1, speedY=1, sizeX=2, sizeY=1; // Размер указывается как "радиус"

	while(1){

		//system("clear");

		for (int y = 0; y < screenY; y++){
			for (int x = 0; x < screenX; x++){
				if ((x >= posX-sizeX && x <= posX+sizeX) && (y >= posY-sizeY && y <= posY+sizeY))
					std::cout << '#';
				else
					std::cout << '-';
			}
			std::cout << std::endl;
		}

		posX += speedX;
		posY += speedY;

		// Проверка на столкновения
		if (posX - sizeX <= 1)speedX *= -1;//posX = sizeX;
		if (posX + sizeX >= screenX-1)speedX *= -1;//posX = screenX-sizeX;
		if (posY - sizeY <= 1)speedY *= -1;//posY = sizeY;
		if (posY + sizeY >= screenY-1)speedY *= -1;//posY = screenY-sizeY;

		sleep_for(nanoseconds(100*1000000));
		
		//system("clear");
	}
	return 0;
}

