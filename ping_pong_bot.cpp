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

	const char Pchar[6][4] = {
		{'P', 'P', 'P', ' '},
		{'P', ' ', ' ', 'P'},
		{'P', 'P', 'P', ' '},
		{'P', ' ', ' ', ' '},
		{'P', ' ', ' ', ' '},
		{'P', ' ', ' ', ' '}
	};

	const char Lchar[6][4] = {
		{'L', ' ', ' ', ' '},
		{'L', ' ', ' ', ' '},
		{'L', ' ', ' ', ' '},
		{'L', ' ', ' ', ' '},
		{'L', ' ', ' ', ' '},
		{'L', 'L', 'L', 'L'}
	};

	const char Achar[6][4] = {
		{' ', 'A', 'A', ' '},
		{'A', ' ', ' ', 'A'},
		{'A', ' ', ' ', 'A'},
		{'A', 'A', 'A', 'A'},
		{'A', ' ', ' ', 'A'},
		{'A', ' ', ' ', 'A'}
	};

	const char Ychar[6][4] = {
		{'Y', ' ', ' ', 'Y'},
		{' ', 'Y', 'Y', ' '},
		{' ', 'Y', 'Y', ' '},
		{' ', 'Y', 'Y', ' '},
		{' ', 'Y', 'Y', ' '},
		{' ', 'Y', 'Y', ' '}
	};

	const char Echar[6][4] = {
		{'E', 'E', 'E', 'E'},
		{'E', ' ', ' ', ' '},
		{'E', 'E', 'E', 'E'},
		{'E', ' ', ' ', ' '},
		{'E', ' ', ' ', ' '},
		{'E', 'E', 'E', 'E'}
	};

	const char Rchar[6][4] = {
		{'R', 'R', 'R', ' '},
		{'R', ' ', ' ', 'R'},
		{'R', 'R', 'R', ' '},
		{'R', 'R', ' ', ' '},
		{'R', ' ', 'R', ' '},
		{'R', ' ', ' ', 'R'}
	};

	const char Ochar[6][4] = {
		{' ', 'O', 'O', ' '},
		{'O', ' ', ' ', 'O'},
		{'O', ' ', ' ', 'O'},
		{'O', ' ', ' ', 'O'},
		{'O', ' ', ' ', 'O'},
		{' ', 'O', 'O', ' '}
	};

	const char Ichar[6][4] = {
		{'I', 'I', 'I', 'I'},
		{' ', 'I', 'I', ' '},
		{' ', 'I', 'I', ' '},
		{' ', 'I', 'I', ' '},
		{' ', 'I', 'I', ' '},
		{'I', 'I', 'I', 'I'}
	};

	const char Nchar[6][4] = {
		{'N', ' ', ' ', 'N'},
		{'N', 'N', ' ', 'N'},
		{'N', 'N', ' ', 'N'},
		{'N', ' ', 'N', 'N'},
		{'N', ' ', 'N', 'N'},
		{'N', ' ', ' ', 'N'}
	};

	const char Tchar[6][4] = {
		{'T', 'T', 'T', 'T'},
		{' ', 'T', 'T', ' '},
		{' ', 'T', 'T', ' '},
		{' ', 'T', 'T', ' '},
		{' ', 'T', 'T', ' '},
		{' ', 'T', 'T', ' '}
	};

	const char Wchar[5][5] = {
		{'W', ' ', 'W', ' ', 'W'},
		{'W', ' ', 'W', ' ', 'W'},
		{'W', ' ', 'W', ' ', 'W'},
		{' ', 'W', ' ', 'W', ' '},
		{' ', 'W', ' ', 'W', ' '},
	};


	const char plusChar[6][6] = {
		{' ', ' ', '+', '+', ' ', ' '},
		{' ', ' ', '+', '+', ' ', ' '},
		{'+', '+', '+', '+', '+', '+'},
		{'+', '+', '+', '+', '+', '+'},
		{' ', ' ', '+', '+', ' ', ' '},
		{' ', ' ', '+', '+', ' ', ' '}
	};

	switch (ch) {
		case '0': out = zeroChar[y][x]; break;
		case '1': out = oneChar[y][x]; break;
		case '2': out = twoChar[y][x]; break;
		case '3': out = threeChar[y][x]; break;
		case ':': out = colonChar[y][x]; break;
		case 'b': out = ballChar[y][x]; break;
		case 'P': out = Pchar[y][x]; break;
		case 'L': out = Lchar[y][x]; break;
		case 'A': out = Achar[y][x]; break;
		case 'Y': out = Ychar[y][x]; break;
		case 'E': out = Echar[y][x]; break;
		case 'R': out = Rchar[y][x]; break;
		case 'O': out = Ochar[y][x]; break;
		case 'I': out = Ichar[y][x]; break;
		case 'N': out = Nchar[y][x]; break;
		case 'T': out = Tchar[y][x]; break;
		case 'W': out = Wchar[y][x]; break;
		case '+': out = plusChar[y][x]; break;
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
				else std::cout << "-";
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
				else std::cout << "-";
			}
			std::cout << std::endl;
	}
	sleep_for(nanoseconds(2000*1000000));
	exit(0);

}


int main() {
	using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

	//========================== Инциализация переменных ==========================//
	struct winsize w;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	w.ws_row -= 1;

	char ch;
	bool plWin;
	int defaultSqrSetPosX = static_cast<int>(w.ws_col/2), defaultSqrSetPosY = static_cast<int>(w.ws_row/2), 
			defaultSqrSetSpeedX = 3, defaultSqrSetSpeedY = 2;
	//square sqr = {10, 10, 1, 1, 2, 1};
	square sqr = {defaultSqrSetPosX, defaultSqrSetPosY, defaultSqrSetSpeedX, defaultSqrSetSpeedY, 4, 2};

	player leftPl = {20, 0, 4, 10};
	player rightPl = {10, 0, 4, 10};
	
	prediction pred;
	//========================== Инциализация переменных ==========================//

  //std::random_device rd;
	//std::mt19937 eng(rd());
	//std::uniform_int_distribution<> distr(-3, 3);
	
	auto movePlRand = std::bind(std::uniform_int_distribution<>(-3,3),std::default_random_engine());
	auto winPlRand = std::bind(std::uniform_int_distribution<>(0,2),std::default_random_engine());
	
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
			//if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) return 0;
			//square sqr = {defaultSqrSetPosX, defaultSqrSetPosY, defaultSqrSetSpeedX, defaultSqrSetSpeedY, 4, 2};

			if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) {
				newPointPlayer(2, w);
				rightPl.score++;
				sqr.posX = defaultSqrSetPosX;
				sqr.posY = defaultSqrSetPosY;
				sqr.speedX = defaultSqrSetSpeedX;
				sqr.speedY = defaultSqrSetSpeedY;
			}
			sqr.speedX *= -1;

			pred = calcPred(sqr, leftPl.width, rightPl.width, w);
			plWin = winPlRand();
		}
		else if (sqr.posX + sqr.sizeX >= w.ws_col - rightPl.width - 1) {
			//if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) return 0;
			if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
				newPointPlayer(1, w);
				leftPl.score++;
				sqr.posX = defaultSqrSetPosX;
				sqr.posY = defaultSqrSetPosY;
				sqr.speedX = defaultSqrSetSpeedX;
				sqr.speedY = defaultSqrSetSpeedY;
			}
			sqr.speedX *= -1;

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
		
		//playerWinScreen(2, w);
		
		system("clear");
		//write(1,"\E[H\E[2J",7);
		for (int y = 0; y < w.ws_row; y++){
			for (int x = 0; x < w.ws_col; x++){

				//char numCh1 = drawChar('2', 10, 10, x, y);

				//if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
				//	std::cout << '#';
				if (drawChar('b', sqr.posX-sqr.sizeX, sqr.posY-sqr.sizeY, x, y, 9, 5)) {}

				else if ((sqr.speedX > 0 && x >= w.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
					std::cout << "\x1B[36mX\033[0m";

				else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
						(x >= w.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
					std::cout << '@';

				else if (drawChar(':', static_cast<int>(w.ws_col/2) - 2, 1, x, y, 4, 6)) {}
				else if (drawChar(leftPl.score + '0', static_cast<int>(w.ws_col/2) - 6, 1, x, y, 4, 6)) {}
				else if (drawChar(rightPl.score + '0', static_cast<int>(w.ws_col/2) + 2, 1, x, y, 4, 6)) {}

				//else if (drawChar('P', 5, 6, x, y, 4, 6)) {}
				//else if (drawChar('1', 20, 10, x, y, 4, 6)) {}
				//else if (drawChar('2', 30, 10, x, y, 4, 6)) {}
				//else if (drawChar('3', 40, 10, x, y, 4, 6)) {}

				else std::cout << '-';
			}
			std::cout << std::endl;
		}
		//========================== Отрисовка ==========================//

		sleep_for(nanoseconds(30*1000000));
		//sleep_for(nanoseconds(1000));

		//std::cout << "w.ws_col = " << w.ws_col << "; w.ws_row = " << w.ws_row << "; posX = " << sqr.posX << "; posY = " << sqr.posY << "; leftPlPos = " << leftPl.pos << "; rightPlPos = " << rightPl.pos << "; speedX = " << sqr.speedX << "; speedY = " << sqr.speedY << "; pred = " << pred.pred << "; predTime = " << pred.predTime;

		//ch = getchar();
		//if (ch == 'q') return 0;
		//else if (ch == 'c') system("clear");

	}
	return 0;
}

