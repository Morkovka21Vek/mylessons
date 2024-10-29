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
	const int width;
	const int height;
};

struct prediction {
	int pred;
	int predTime;
};

prediction calcPred(square sqr, int leftMargin, int rightMargin, winsize w) {
	int predTime = 0;
	square sqrPred = sqr;

	while (1) {
		sqrPred.posX += sqrPred.speedX;
		sqrPred.posY += sqrPred.speedY;

		if (sqrPred.posY - sqrPred.sizeY <= 0)sqrPred.speedY *= -1;
		else if (sqrPred.posY + sqrPred.sizeY >= w.ws_row-1)sqrPred.speedY *= -1;

		if (sqrPred.posX + sqrPred.sizeX >= w.ws_col - rightMargin - 1) break;
		else if (sqrPred.posX - sqrPred.sizeX <= leftMargin) break;

		predTime++;
	}	
	prediction pred = {sqrPred.posY, predTime};

	return pred;
}


int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

	char ch;
	//int posX=10, posY=10, speedX=1, speedY=1;
	square sqr = {10, 10, 1, 1, 2, 1};
	//const int sizeX=2, sizeY=1; // Размер указывается как "радиус"

	//float leftPlPos=0, rightPlPos=0;
	//const int plSizeX=4, plSizeY=10;
	
	player leftPl = {0, 4, 10};
	player rightPl = {0, 4, 10};

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 2;

	prediction pred;

	//std::random_device rd;
	//std::mt19937 eng(rd());
	//std::uniform_int_distribution<> distr(-5, 5);
	
	//predPosX = posX;
	//predPosY = posY;
	//predSpeedY = speedY;
	//predTime = 0;
	
	pred = calcPred(sqr, leftPl.width, rightPl.width, w);
	std::cout << "pred = " << pred.pred << "; predTime = " << pred.predTime << std::endl;
	getchar();
	system("clear");

/*
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
	}*/



	while(1){

		pred.predTime--;

		system("clear");

		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){

				if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
					std::cout << '#';

				else if ((sqr.speedX > 0 && x >= w.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
					std::cout << "\x1B[36mX\033[0m";

				else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
						(x >= w.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
					std::cout << '@';

				else
					std::cout << ' ';
			}
			std::cout << std::endl;
		}

		sqr.posX += sqr.speedX;
		sqr.posY += sqr.speedY;

		//leftPlPos += distr(eng);
		//rightPlPos += distr(eng);

		//rightPlPos = leftPlPos = posY - static_cast<int>(plSizeY/2);

		leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime / 3);
		rightPl.pos = rightPl.pos + (pred.pred - rightPl.pos - static_cast<int>(rightPl.height/2)) / (pred.predTime / 3);

		//predPosX = posX;
		//predPosY = posY;
		//predSpeedY = speedY;

		if (leftPl.pos < 0) leftPl.pos = 0;
		else if (leftPl.pos + leftPl.height > w.ws_row) leftPl.pos = w.ws_row - leftPl.height;

		if (rightPl.pos < 0) rightPl.pos = 0;
		else if (rightPl.pos + rightPl.height > w.ws_row) rightPl.pos = w.ws_row - rightPl.height;

		// Проверка на столкновения
		if (sqr.posX - sqr.sizeX <= leftPl.width) {
			if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) return 0;
			//posX = sizeX+plSizeX;
			sqr.speedX *= -1;

			/*predTime = 0;
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
			predTime += 2;*/
			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
		}
		else if (sqr.posX + sqr.sizeX >= w.ws_col - rightPl.width - 1) {
			std::cout << "sizeY = " << sqr.sizeY << ";  rightPl.pos = " << rightPl.pos << ";  rightPl.height = " << rightPl.height;
			if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) return 0;
				//posX = screenX-sizeX;
				sqr.speedX *= -1;

				/*predTime = 0;
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
			predTime += 2;*/
				pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			}
	
		if (sqr.posY - sqr.sizeY <= 0)sqr.speedY *= -1;//posY = sizeY;
		else if (sqr.posY + sqr.sizeY >= w.ws_row-1)sqr.speedY *= -1;//posY = screenY-sizeY;
		

		//sleep_for(nanoseconds(30*1000000));

		std::cout << "posX = " << sqr.posX << "; posY = " << sqr.posY << "; leftPlPos = " << leftPl.pos << "; rightPlPos = " << rightPl.pos << "; speedX = " << sqr.speedX << "; speedY = " << sqr.speedY << "; pred = " << pred.pred << "; predTime = " << pred.predTime << std::endl;
		if (getchar() == 'q') return 0;
		//system("clear");
	}
	return 0;
}

