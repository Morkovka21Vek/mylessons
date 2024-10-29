#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>

#include <chrono>
#include <thread>

#include <random>

struct square {
	int posX;
	int posY;
	int speedX;
	int speedY;
	const int sizeX;
	const int sizeY;
};

struct player {
	int pos;
	const int sizeX;
	const int sizeY
};

int calcPred(square sqr) {
	int predTime = 0;
	while (1) {
		predPosX += speedX;
		predPosY += predSpeedY;

		if (predPosY - sizeY <= 0)predSpeedY *= -1;
		else if (predPosY + sizeY >= w.ws_row-1)predSpeedY *= -1;

		if (predPosX + sizeX >= w.ws_col - plSizeX - 1) {
			pred = predPosY;
			break;
		} else if (predPosX - sizeX <= plSizeX) {
			pred = predPosY;
			break;
		}

		predTime++;
	}
	return pred, predTime;
}


int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

	char ch;
	//int posX=10, posY=10, speedX=1, speedY=1;
	//const int sizeX=2, sizeY=1; // Размер указывается как "радиус"

	//float leftPlPos=0, rightPlPos=0;
	//const int plSizeX=4, plSizeY=10;

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 2;

	int pred, predPosX, predPosY, predSpeedY, predTime;

	//std::random_device rd;
	//std::mt19937 eng(rd());
	//std::uniform_int_distribution<> distr(-5, 5);
	
	//predPosX = posX;
	//predPosY = posY;
	//predSpeedY = speedY;
	//predTime = 0;

	while (1) {
		predPosX += speedX;
		predPosY += predSpeedY;

		if (predPosY - sizeY <= 0)predSpeedY *= -1;
		else if (predPosY + sizeY >= w.ws_row-1)predSpeedY *= -1;

		if (predPosX + sizeX >= w.ws_col - plSizeX - 1) {
			pred = predPosY;
			break;
		}
		predTime++;
	}


	while(1){

		predTime--;

		system("clear");

		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){
				if ((x >= posX-sizeX && x <= posX+sizeX) && (y >= posY-sizeY && y <= posY+sizeY))
					std::cout << '#';
				else if ((speedX > 0 && x >= w.ws_col - plSizeX && y == pred) || (speedX < 0 && x < plSizeX && y == pred)) 
					std::cout << "\x1B[36mX\033[0m";
				else if ((x < plSizeX && (y >= leftPlPos && y < leftPlPos + plSizeY)) || (x >= w.ws_col - plSizeX && (y >= rightPlPos && y < rightPlPos + plSizeY)))
					std::cout << '@';
				else
					std::cout << ' ';
			}
			std::cout << std::endl;
		}

		posX += speedX;
		posY += speedY;

		//leftPlPos += distr(eng);
		//rightPlPos += distr(eng);

		//rightPlPos = leftPlPos = posY - static_cast<int>(plSizeY/2);

		rightPlPos = leftPlPos = leftPlPos + (pred - leftPlPos - static_cast<int>(plSizeY/2)) / (predTime / 2);

		predPosX = posX;
		predPosY = posY;
		predSpeedY = speedY;

		if (leftPlPos < 0) leftPlPos = 0;
		else if (leftPlPos + plSizeY > w.ws_row) leftPlPos = w.ws_row - plSizeY;

		if (rightPlPos < 0) rightPlPos = 0;
		else if (rightPlPos + plSizeY > w.ws_row) rightPlPos = w.ws_row - plSizeY;

		// Проверка на столкновения
		if (posX - sizeX <= plSizeX) {
			if (!(posY+sizeY >= leftPlPos && posY-sizeY < leftPlPos + plSizeY)) return 0;
			//posX = sizeX+plSizeX;
			speedX *= -1;

			predTime = 0;
			while (1) {
				predPosX += speedX;
				predPosY += predSpeedY;

				if (predPosY - sizeY <= 0)predSpeedY *= -1;
				else if (predPosY + sizeY >= w.ws_row-1)predSpeedY *= -1;

				if (predPosX + sizeX >= w.ws_col - plSizeX - 1) {
					pred = predPosY;
					break;
				}
				predTime++;
			}
			predTime += 2;
		}
		else if (posX + sizeX >= w.ws_col - plSizeX - 1) {
			if (!(posY+sizeY >= rightPlPos && posY-sizeY < rightPlPos + plSizeY)) return 0;
				//posX = screenX-sizeX;
				speedX *= -1;

				predTime = 0;
				while (1) {
					predPosX += speedX;
					predPosY += predSpeedY;

					if (predPosY - sizeY <= 0)predSpeedY *= -1;
					else if (predPosY + sizeY >= w.ws_row-1)predSpeedY *= -1;

					if (predPosX - sizeX <= plSizeX) {
						pred = predPosY;
						break;
					}
					predTime++;
				}
			predTime += 2;
			}
	
		if (posY - sizeY <= 0)speedY *= -1;//posY = sizeY;
		else if (posY + sizeY >= w.ws_row-1)speedY *= -1;//posY = screenY-sizeY;
		

		//sleep_for(nanoseconds(30*1000000));

		std::cout << "posX = " << posX << "; posY = " << posY << "; leftPlPos = " << leftPlPos << "; rightPlPos = " << rightPlPos << "; speedX = " << speedX << "; speedY = " << speedY << "; pred = " << pred << "; predTime = " << predTime << std::endl;
		if (getchar() == 'q') return 0;
		//system("clear");
	}
	return 0;
}

