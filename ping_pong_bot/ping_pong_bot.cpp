//========================== Импорт заголовочных файлов ==========================//
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <cstdlib>

#include <iostream>
#include <iomanip>

#include <chrono>
#include <thread>

#include <random>
#include <functional>
#include "assets.h"
//========================== Импорт заголовочных файлов ==========================//

char backgroundColor = ' ';

//========================== Объявление структур ==========================//
struct square {
	int posX;
	int posY;
	int speedX;
	int speedY;
	int sizeX;
	int sizeY;
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


bool drawChar (char ch, int posX, int posY, int x, int y, int width, int height) {
	char outCh = ' ';
	if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
		outCh = getSymbolCh (ch, x - posX, y - posY);
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

		//if (sqrPred.posX + sqrPred.sizeX >= w.ws_col - rightMargin - 1) break;
		//else if (sqrPred.posX - sqrPred.sizeX <= leftMargin) break;
	}	

	prediction pred = {sqrPred.posY, predTime};
	return pred;
}

void newPointPlayer(int player, winsize w) {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds
	
	system("clear");
	sleep_for(nanoseconds(500*1000000));

	int centerScrX = static_cast<int>(w.ws_col / 2);
	int centerScrY = static_cast<int>(w.ws_row / 2) - 3;

	for (int y = 0; y < w.ws_row; y++){    
    	for (int x = 0; x < w.ws_col; x++){
				if (drawChar('P', centerScrX-35, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('L', centerScrX-30, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('A', centerScrX-25, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('Y', centerScrX-20, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('E', centerScrX-15, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('R', centerScrX-10, centerScrY, x, y, 4, 6)) {}
				else if (drawChar(player + '0', centerScrX-2, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('+', centerScrX+8, centerScrY, x, y, 6, 6)) {}
				else if (drawChar('1', centerScrX+15, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('P', centerScrX+25, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('O', centerScrX+30, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('I', centerScrX+35, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('N', centerScrX+40, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('T', centerScrX+45, centerScrY, x, y, 4, 6)) {}
				else std::cout << backgroundColor;
			}
			std::cout << std::endl;
	}
	sleep_for(nanoseconds(2000*1000000));
	//getchar();
}

void playerWinScreen (int player, winsize w) {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds
															 
	//w.ws_row--;
	
	system("clear");
	sleep_for(nanoseconds(500*1000000));

	int centerScrX = static_cast<int>(w.ws_col / 2);
	int centerScrY = static_cast<int>(w.ws_row / 2) - 3;

	for (int y = 0; y < w.ws_row; y++){    
    	for (int x = 0; x < w.ws_col; x++){
				if (drawChar('P', centerScrX-32, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('L', centerScrX-27, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('A', centerScrX-22, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('Y', centerScrX-17, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('E', centerScrX-12, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('R', centerScrX-7, centerScrY, x, y, 4, 6)) {}
				else if (drawChar(player + '0', centerScrX+2, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('W', centerScrX+10, centerScrY+1, x, y, 5, 5)) {}
				else if (drawChar('I', centerScrX+16, centerScrY, x, y, 4, 6)) {}
				else if (drawChar('N', centerScrX+21, centerScrY, x, y, 4, 6)) {}
				else std::cout << backgroundColor;
			}
			std::cout << std::endl;
	}
	sleep_for(nanoseconds(2000*1000000));
	exit(0);

}

int timeToFps (int time) {
  if (time == 0)
    return 0;
  else
    return static_cast<int>(1000/time);
}

int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
	//========================== Инциализация переменных ==========================//
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 1;


  //std::chrono::_V2::system_clock::time_point fpsFrameTime, fpsStartTime, fpsEndTime;
  auto fpsStartTime = std::chrono::high_resolution_clock::now(), fpsEndTime = std::chrono::high_resolution_clock::now();
  auto fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsStartTime - fpsEndTime);

	char ch;
	bool plWin;
  const square defaultSqr = {static_cast<int>(w.ws_col/2), static_cast<int>(w.ws_row/2), 3, 2, 4, 2};
  square sqr = defaultSqr;

	player leftPl = {20, 0, 4, 10};
	player rightPl = {10, 0, 4, 10};
	
	prediction pred;
  //fpsEndTime = fpsStartTime = std::chrono::high_resolution_clock::now();
	//========================== Инциализация переменных ==========================//

	auto movePlRand = std::bind(std::uniform_int_distribution<>(-3,3),std::default_random_engine());
	auto winPlRand = std::bind(std::uniform_int_distribution<>(0,2),std::default_random_engine());
	
	pred = calcPred(sqr, leftPl.width, rightPl.width, w);
	//std::cout << "pred = " << pred.pred << "; predTime = " << pred.predTime << std::endl;
	//getchar();
	//system("clear");

	while(1){

    fpsStartTime = std::chrono::high_resolution_clock::now();

		sqr.posX += sqr.speedX;
		sqr.posY += sqr.speedY;

		//========================== Проверка на столкновения ==========================//
		if (sqr.posY - sqr.sizeY <= 0) sqr.speedY *= -1;
		else if (sqr.posY + sqr.sizeY >= w.ws_row-1) sqr.speedY *= -1;

		
		if (sqr.posX - sqr.sizeX <= leftPl.width) {
			sqr.speedX *= -1;
			if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) {
				newPointPlayer(2, w);
				rightPl.score++;
				sqr = defaultSqr;
			}

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			plWin = winPlRand();
		}
		else if (sqr.posX + sqr.sizeX >= w.ws_col - rightPl.width - 1) {
			sqr.speedX *= -1;
			if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
				newPointPlayer(1, w);
				leftPl.score++;
				sqr = defaultSqr;
			}

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			plWin = winPlRand();
		}
	
		//========================== Проверка на столкновения ==========================//

		if (leftPl.score >= 3) playerWinScreen (1, w);
		else if (rightPl.score >= 3) playerWinScreen (2, w);


		//========================== Изменение положения и проверка игрока ==========================//
		//leftPl.pos += distr(eng);
		//rightPl.pos += distr(eng);
		//rightPl.pos = leftPl.pos = sqr.posY - static_cast<int>(leftPl.height/2);
		//pred = calcPred(sqr, leftPl.width, rightPl.width, w);

		int randomVar = movePlRand();
		int randomVarModule = (randomVar < 0) ? -randomVar : randomVar;
		if (!plWin)
			leftPl.pos = leftPl.pos + (pred.pred - randomVar - leftPl.pos - leftPl.height) / (pred.predTime + randomVarModule) + randomVar;
		else
			leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime) + randomVar;

		randomVar = movePlRand();
		randomVarModule = (randomVar < 0) ? -randomVar : randomVar;
		if (!plWin)
			rightPl.pos = rightPl.pos + (pred.pred - randomVar - rightPl.pos - rightPl.height) / (pred.predTime + randomVarModule) + randomVar;
		else
			rightPl.pos = rightPl.pos + (pred.pred - rightPl.pos - static_cast<int>(rightPl.height/2)) / (pred.predTime) + randomVar;

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
    //std::cout << "\033[2J\033[1;1H";
     
    std::cout << std::setfill(backgroundColor) << std::setw(7) << "\x1B[92m" << timeToFps(fpsFrameTime.count()) << "FPS\033[0m";

		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){

				//if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
				//	std::cout << '#';
        if (y == 0 && x <= 6) {}
        else if (drawChar('b', sqr.posX-sqr.sizeX, sqr.posY-sqr.sizeY, x, y, 9, 5)) {}

				else if ((sqr.speedX > 0 && x >= w.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
					std::cout << "\x1B[36mX\033[0m";

				else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
						(x >= w.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
					std::cout << '@';

				else if (drawChar(':', static_cast<int>(w.ws_col/2) - 2, 1, x, y, 4, 6)) {}
				else if (drawChar(leftPl.score + '0', static_cast<int>(w.ws_col/2) - 6, 1, x, y, 4, 6)) {}
				else if (drawChar(rightPl.score + '0', static_cast<int>(w.ws_col/2) + 2, 1, x, y, 4, 6)) {}

				else std::cout << backgroundColor;
			}
			std::cout << std::endl;
		}
		//========================== Отрисовка ==========================//

		sleep_for(nanoseconds(30*1000000));

    fpsEndTime = std::chrono::high_resolution_clock::now();
    fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsEndTime - fpsStartTime );

		//std::cout << "w.ws_col = " << w.ws_col << "; w.ws_row = " << w.ws_row << "; posX = " << sqr.posX << "; posY = " << sqr.posY << "; leftPlPos = " << leftPl.pos << "; rightPlPos = " << rightPl.pos << "; speedX = " << sqr.speedX << "; speedY = " << sqr.speedY << "; pred = " << pred.pred << "; predTime = " << pred.predTime;

		//ch = getchar();
		//if (ch == 'q') return 0;
		//else if (ch == 'c') system("clear");

	}
	return 0;
}

