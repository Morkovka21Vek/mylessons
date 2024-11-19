//========================== Импорт заголовочных файлов ==========================//
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>

#include <chrono>
#include <thread>

#include <random>
#include <functional>
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
	int score;
	const int width;
	const int height;
};

struct prediction {
	int pred;
	int predTime;
};
//========================== Объявление структур ==========================//

char getSymbolCh (char ch, int x, int y) {
	char out = 'E';


	const char zeroChar[6][4] = {
		{'0', '0', '0', '0'},
		{'0', ' ', ' ', '0'},
		{'0', ' ', ' ', '0'},
		{'0', ' ', ' ', '0'},
		{'0', ' ', ' ', '0'},
		{'0', '0', '0', '0'}
	};


	const char oneChar[6][4] = {
		{' ', '1', '1', ' '},
		{' ', '1', '1', ' '},
		{' ', '1', '1', ' '},
		{' ', '1', '1', ' '},
		{' ', '1', '1', ' '},
		{' ', '1', '1', ' '}
	};

	const char twoChar[6][4] = {
		{'2', '2', '2', '2'},
		{' ', ' ', ' ', '2'},
		{'2', '2', '2', '2'},
		{'2', ' ', ' ', ' '},
		{'2', ' ', ' ', ' '},
		{'2', '2', '2', '2'}
	};

	const char threeChar[6][4] = {
		{'3', '3', '3', '3'},
		{' ', ' ', ' ', '3'},
		{'3', '3', '3', '3'},
		{' ', ' ', ' ', '3'},
		{' ', ' ', ' ', '3'},
		{'3', '3', '3', '3'}
	};

	const char colonChar[6][4] = {
		{' ', '#', '#', ' '},
		{' ', '#', '#', ' '},
		{' ', ' ', ' ', ' '},
		{' ', ' ', ' ', ' '},
		{' ', '#', '#', ' '},
		{' ', '#', '#', ' '}
	};

	const char ballChar[5][9] = {
		{' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
		{' ', '#', '#', '#', '#', '#', '#', '#', ' '},
		{'#', '#', '#', '#', '#', '#', '#', '#', '#'},
		{' ', '#', '#', '#', '#', '#', '#', '#', ' '},
		{' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
	};


	switch (ch) {
		case '0':
			out = zeroChar[y][x];
			break;

		case '1':
			out = oneChar[y][x];
			break;

		case '2':
			out = twoChar[y][x];
			break;

		case '3':
			out = threeChar[y][x];
			break;

		case ':':
			out = colonChar[y][x];
			break;

		case 'B':
			out = ballChar[y][x];
			break;
	}
	return out;
}

bool drawChar (char ch, int posX, int posY, int x, int y, int width, int height) {
	char outCh = ' ';
	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		outCh = getSymbolCh (ch, x - posX, y - posY);
		//std::cout << std::endl << "ch = " << ch << ";  x-posX = " << x - posX << ";  y-posY = " << y - posY << ";  outCh = " << outCh << std::endl;
		if (outCh != ' ') std::cout << outCh;
	}
	return (outCh != ' ');
}


prediction calcPred(square sqr, int leftMargin, int rightMargin, winsize w) {
	int predTime = 0;
	square sqrPred = sqr;

	//std::cout << "\x1B[32m";

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
	int debugPredTime = 0;
	char ch;
	bool plWin;
	//square sqr = {10, 10, 1, 1, 2, 1};
	square sqr = {10, 10, 1, 1, 4, 2};

	player leftPl = {20, 0, 4, 10};
	player rightPl = {10, 0, 4, 10};

	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 1;

	prediction pred;
	//========================== Инциализация переменных ==========================//

  //std::random_device rd;
	//std::mt19937 eng(rd());
	//std::uniform_int_distribution<> distr(-3, 3);
	
	auto movePlRand = std::bind(std::uniform_int_distribution<>(-3,3),std::default_random_engine());
	auto winPlRand = std::bind(std::uniform_int_distribution<>(0,5),std::default_random_engine());
	
	pred = calcPred(sqr, leftPl.width, rightPl.width, w);
	//std::cout << "pred = " << pred.pred << "; predTime = " << pred.predTime << std::endl;
	//getchar();
	//system("clear");

	while(1){

		sqr.posX += sqr.speedX;
		sqr.posY += sqr.speedY;

		//========================== Проверка на столкновения ==========================//
		if (sqr.posY - sqr.sizeY <= 0) sqr.speedY *= -1;
		else if (sqr.posY + sqr.sizeY >= w.ws_row-1) sqr.speedY *= -1;

		
		if (sqr.posX - sqr.sizeX <= leftPl.width) {
			//std::cout << "G(H)et colision!" << std::endl;
			//if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) return 0;
			if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) rightPl.score++;
			sqr.speedX *= -1;

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			plWin = winPlRand();
		}
		else if (sqr.posX + sqr.sizeX >= w.ws_col - rightPl.width - 1) {
			//std::cout << "G(H)et colision!" << std::endl;
			//if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) return 0;
			if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) leftPl.score++;
			sqr.speedX *= -1;

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			plWin = winPlRand();
		}
	
		//========================== Проверка на столкновения ==========================//


		//========================== Изменение положения и проверка игрока ==========================//
		//leftPl.pos += distr(eng);
		//rightPl.pos += distr(eng);
		debugPredTime = pred.predTime;
		//rightPl.pos = leftPl.pos = sqr.posY - static_cast<int>(leftPl.height/2);
		//pred = calcPred(sqr, leftPl.width, rightPl.width, w);

		int randomVar = movePlRand();
		int randomVarModule = (randomVar < 0) ? -randomVar : randomVar;
		if (!plWin)
			rightPl.pos = leftPl.pos = leftPl.pos + (pred.pred - randomVar - leftPl.pos - leftPl.height) / (pred.predTime + randomVarModule) + randomVar;
		else
			rightPl.pos = leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime) + randomVar;

		//leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime);
		//rightPl.pos = rightPl.pos + (pred.pred - rightPl.pos - static_cast<int>(rightPl.height/2)) / (pred.predTime);

		if (leftPl.pos < 0) leftPl.pos = 0;
		else if (leftPl.pos + leftPl.height > w.ws_row) leftPl.pos = w.ws_row - leftPl.height;

		if (rightPl.pos < 0) rightPl.pos = 0;
		else if (rightPl.pos + rightPl.height > w.ws_row) rightPl.pos = w.ws_row - rightPl.height;

		pred.predTime--;
		//========================== Изменение и проверка игрока ==========================//

		//========================== Отрисовка ==========================//
		
		system("clear");
		//write(1,"\E[H\E[2J",7);
		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){

				//char numCh1 = drawChar('2', 10, 10, x, y);

				//if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
				//	std::cout << '#';
				if (drawChar('B', sqr.posX-sqr.sizeX, sqr.posY-sqr.sizeY, x, y, 9, 5)) {}

				else if ((sqr.speedX > 0 && x >= w.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
					std::cout << "\x1B[36mX\033[0m";

				else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
						(x >= w.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
					std::cout << '@';

				else if (drawChar(':', static_cast<int>(w.ws_col/2) - 2, 1, x, y, 4, 6)) {}
				else if (drawChar(leftPl.score + '0', static_cast<int>(w.ws_col/2) - 6, 1, x, y, 4, 6)) {}
				else if (drawChar(rightPl.score + '0', static_cast<int>(w.ws_col/2) + 2, 1, x, y, 4, 6)) {}
				//else if (drawChar('1', 20, 10, x, y, 4, 6)) {}
				//else if (drawChar('2', 30, 10, x, y, 4, 6)) {}
				//else if (drawChar('3', 40, 10, x, y, 4, 6)) {}

				else std::cout << '-';
			}
			std::cout << std::endl;
		}
		//========================== Отрисовка ==========================//

		//sleep_for(nanoseconds(30*1000000));
		sleep_for(nanoseconds(1000));

		std::cout << "w.ws_col = " << w.ws_col << "; w.ws_row = " << w.ws_row << "; posX = " << sqr.posX << "; posY = " << sqr.posY << "; leftPlPos = " << leftPl.pos << "; rightPlPos = " << rightPl.pos << "; speedX = " << sqr.speedX << "; speedY = " << sqr.speedY << "; pred = " << pred.pred << "; predTime = " << pred.predTime << "; debugPredTime = " << debugPredTime;

		//ch = getchar();
		//if (ch == 'q') return 0;
		//else if (ch == 'c') system("clear");

	}
	return 0;
}

