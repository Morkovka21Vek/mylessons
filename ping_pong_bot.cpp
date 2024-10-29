//========================== Импорт заголовочных файлов ==========================//
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>

#include <chrono>
#include <thread>

#include <random>
//========================== Импорт заголовочных файлов ==========================//


//========================== Объявление структур ==========================//
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
//========================== Объявление структур ==========================//

char getNumberCh (char ch, int x, int y) {
	char out = 'E';

	const char oneChar[6][4] = {
		{' ', ' ', '1', ' '},
		{' ', ' ', '1', ' '},
		{' ', ' ', '1', ' '},
		{' ', ' ', '1', ' '},
		{' ', ' ', '1', ' '},
		{' ', ' ', '1', ' '}
	};

	const char twoChar[6][4] = {
		{'2', '2', '2', '2'},
		{' ', ' ', ' ', '2'},
		{'2', '2', '2', '2'},
		{'2', ' ', ' ', ' '},
		{'2', ' ', ' ', ' '},
		{'2', '2', '2', '2'}
	};

	switch (ch) {
		case '1':
			out = oneChar[y][x];
			break;

		case '2':
			out = twoChar[y][x];
			break;
	}
	return out;
}

bool drawNumber (char ch, int posX, int posY, int x, int y) {
	char outCh = ' ';
	if (x >= posX && x < posX + 4 && y >= posY && y < posY + 6) {
		outCh = getNumberCh (ch, x - posX, y - posY);
		//std::cout << std::endl << "ch = " << ch << ";  x-posX = " << x - posX << ";  y-posY = " << y - posY << ";  outCh = " << outCh << std::endl;
		if (outCh != ' ') std::cout << outCh;
	}
	return (outCh != ' ');
}


prediction calcPred(square sqr, int leftMargin, int rightMargin, winsize w) {
	int predTime = 0;
	square sqrPred = sqr;

	while (1) {
		if (sqrPred.posX + sqrPred.sizeX >= w.ws_col - rightMargin - 1 && sqrPred.speedX > 0) break;
		else if (sqrPred.posX - sqrPred.sizeX <= leftMargin && sqrPred.speedX < 0) break;

		predTime++;

		sqrPred.posX += sqrPred.speedX;
		sqrPred.posY += sqrPred.speedY;

		if (sqrPred.posY - sqrPred.sizeY <= 0)sqrPred.speedY *= -1;
		else if (sqrPred.posY + sqrPred.sizeY >= w.ws_row-1)sqrPred.speedY *= -1;

		//std::cout << "X: " << sqrPred.posX << ";    Y: " << sqrPred.posY << std::endl;
		
		//if (sqrPred.posX + sqrPred.sizeX >= w.ws_col - rightMargin - 1) break;
		//else if (sqrPred.posX - sqrPred.sizeX <= leftMargin) break;
	}	

	prediction pred = {sqrPred.posY, predTime};
	return pred;
}


int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

	//========================== Инциализация переменных ==========================//
	char ch;
	bool isRedSqr;
	square sqr = {10, 10, 1, 1, 2, 1};

	player leftPl = {20, 4, 10};
	player rightPl = {10, 4, 10};

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 1;

	prediction pred;
	//========================== Инциализация переменных ==========================//

	//std::random_device rd;
	//std::mt19937 eng(rd());
	//std::uniform_int_distribution<> distr(-5, 5);
	
	pred = calcPred(sqr, leftPl.width, rightPl.width, w);
	//std::cout << "pred = " << pred.pred << "; predTime = " << pred.predTime << std::endl;
	//getchar();
	//system("clear");

	while(1){

		sqr.posX += sqr.speedX;
		sqr.posY += sqr.speedY;

		//========================== Проверка на столкновения ==========================//
		if (sqr.posX - sqr.sizeX <= leftPl.width) {
			std::cout << "G(H)et colision!" << std::endl;
			//if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) isRedSqr = true;
			//else isRedSqr = false;
			//if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) return 0;
			sqr.speedX *= -1;

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
		}
		else if (sqr.posX + sqr.sizeX >= w.ws_col - rightPl.width - 1) {
			std::cout << "G(H)et colision!" << std::endl;
			//if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) isRedSqr = true;
			//else isRedSqr = false;
			//if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) return 0;
			sqr.speedX *= -1;

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
		}
		//else isRedSqr = false;
	
		if (sqr.posY - sqr.sizeY <= 0) sqr.speedY *= -1;
		else if (sqr.posY + sqr.sizeY >= w.ws_row-1) sqr.speedY *= -1;
		//========================== Проверка на столкновения ==========================//


		//========================== Изменение положения и проверка игрока ==========================//
		//leftPl.pos += distr(eng);
		//rightPl.pos += distr(eng);
		rightPl.pos = leftPl.pos = sqr.posY - static_cast<int>(leftPl.height/2);

		//leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime / 3);
		//rightPl.pos = rightPl.pos + (pred.pred - rightPl.pos - static_cast<int>(rightPl.height/2)) / (pred.predTime / 3);

		if (leftPl.pos < 0) leftPl.pos = 0;
		else if (leftPl.pos + leftPl.height > w.ws_row) leftPl.pos = w.ws_row - leftPl.height;

		if (rightPl.pos < 0) rightPl.pos = 0;
		else if (rightPl.pos + rightPl.height > w.ws_row) rightPl.pos = w.ws_row - rightPl.height;

		pred.predTime--;
		//========================== Изменение и проверка игрока ==========================//

		//========================== Отрисовка ==========================//
		system("clear");
		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){

				//char numCh1 = drawNumber('2', 10, 10, x, y);

				if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
					if (isRedSqr)
						std::cout << "\x1B[31m#\033[0m";
					else
						std::cout << '#';

				else if ((sqr.speedX > 0 && x >= w.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
					std::cout << "\x1B[36mX\033[0m";

				else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
						(x >= w.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
					std::cout << '@';

				else if (drawNumber('2', 10, 10, x, y)) {}

				else std::cout << '-';
			}
			std::cout << std::endl;
		}
		//========================== Отрисовка ==========================//

		//sleep_for(nanoseconds(30*1000000));

		std::cout << "posX = " << sqr.posX << "; posY = " << sqr.posY << "; leftPlPos = " << leftPl.pos << "; rightPlPos = " << rightPl.pos << "; speedX = " << sqr.speedX << "; speedY = " << sqr.speedY << "; pred = " << pred.pred << "; predTime = " << pred.predTime;

		ch = getchar();
		if (ch == 'q') return 0;
		else if (ch == 'c') system("clear");

	}
	return 0;
}

