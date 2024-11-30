//    _             __  __            _              _         ____  ___     __   _    
//   | |__  _   _  |  \/  | ___  _ __| | _______   _| | ____ _|___ \/ \ \   / /__| | __
//   | '_ \| | | | | |\/| |/ _ \| '__| |/ / _ \ \ / / |/ / _` | __) | |\ \ / / _ \ |/ /
//   | |_) | |_| | | |  | | (_) | |  |   < (_) \ V /|   < (_| |/ __/| | \ V /  __/   < 
//   |_.__/ \__, | |_|  |_|\___/|_|  |_|\_\___/ \_/ |_|\_\__,_|_____|_|  \_/ \___|_|\_\
//          |___/                                                                      

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
#include <vector>
#include <algorithm>
//========================== Импорт заголовочных файлов ==========================//

#ifndef BACKCHAR
  #define BACKGROUND_CHAR '-'
#else
  #define BACKGROUND_CHAR BACKCHAR
#endif

#ifndef DEBUG
  #define DEBUG 0
#else
  #define DEBUG 1
#endif

//========================== Объявление структур ==========================//
struct square {
  float posX;
  float posY;
  float speedX;
  float speedY;
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
  float pred;
  int predTime;
  std::vector<int> pathX;
  std::vector<int> pathY;
};
//========================== Объявление структур ==========================//


prediction calcPred(square sqrPred, int leftMargin, int rightMargin, winsize);
void playerWinScreen (int player, winsize);
void newPointPlayer (int player, winsize);
bool drawChar (enum charsEnum chEn, int posX, int posY, int x, int y);
inline bool pathFind(prediction pred, int x, int y);

int main() {
  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::duration;
  using std::chrono::milliseconds;
  //========================== Инциализация переменных ==========================//
  struct winsize windowSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
  windowSize.ws_row -= 1;


  auto fpsStartTime = std::chrono::high_resolution_clock::now(), fpsEndTime = std::chrono::high_resolution_clock::now();
  auto fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsStartTime - fpsEndTime);
  std::vector<int> fps_vector = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  bool plWin;
  const square defaultSqr = {static_cast<float>(windowSize.ws_col/2), static_cast<float>(windowSize.ws_row/2), 1, 0.5F, 4, 2};
  square sqr = defaultSqr;

  player leftPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};
  player rightPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};

  prediction pred;

  //========================== Инциализация переменных ==========================//

  auto movePlRand = std::bind(std::uniform_int_distribution<>(-3,3),std::default_random_engine());
  auto winPlRand = std::bind(std::uniform_int_distribution<>(0,2),std::default_random_engine());
  
  pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize);

  while(1){

    fpsStartTime = std::chrono::high_resolution_clock::now();

    sqr.posX += sqr.speedX;
    sqr.posY += sqr.speedY;

    pred.pathX.erase(pred.pathX.begin());
    pred.pathY.erase(pred.pathY.begin());
    //========================== Проверка на столкновения ==========================//
    if (sqr.posY - sqr.sizeY <= 0) sqr.speedY *= -1;
    else if (sqr.posY + sqr.sizeY >= windowSize.ws_row-1) sqr.speedY *= -1;

    
    if (sqr.posX - sqr.sizeX <= leftPl.width) {
      sqr.speedX *= -1;
      if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) {
        newPointPlayer(2, windowSize);
        rightPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize);
      plWin = winPlRand();
    }
    else if (sqr.posX + sqr.sizeX >= windowSize.ws_col - rightPl.width - 1) {
      sqr.speedX *= -1;
      if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
        newPointPlayer(1, windowSize);
        leftPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize);
      plWin = winPlRand();
    }
  
    //========================== Проверка на столкновения ==========================//

    if (leftPl.score >= 3) playerWinScreen (1, windowSize);
    else if (rightPl.score >= 3) playerWinScreen (2, windowSize);


    //========================== Изменение положения и проверка игрока ==========================//
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
    else if (leftPl.pos + leftPl.height > windowSize.ws_row) leftPl.pos = windowSize.ws_row - leftPl.height;

    if (rightPl.pos < 0) rightPl.pos = 0;
    else if (rightPl.pos + rightPl.height > windowSize.ws_row) rightPl.pos = windowSize.ws_row - rightPl.height;

    pred.predTime--;
    //========================== Изменение и проверка игрока ==========================//

    //========================== Отрисовка ==========================//
    
    system("clear");
 
    int fpsCount = (fpsFrameTime.count() == 0) ? 0 : static_cast<int>(1000/fpsFrameTime.count());
    fps_vector.push_back(fpsCount);
    fps_vector.erase(fps_vector.begin());
    int meanFps = static_cast<int> (accumulate(fps_vector.begin(), fps_vector.end(), 0) / fps_vector.size());
    std::cout << std::setfill(BACKGROUND_CHAR) << std::setw(7) << "\x1B[92m" << meanFps << "FPS\033[0m";

    for (int y = 0; y < windowSize.ws_row; y++){
      for (int x = 0; x < windowSize.ws_col; x++){
        //if ((x >= sqr.posX-sqr.sizeX && x <= sqr.posX+sqr.sizeX) && (y >= sqr.posY-sqr.sizeY && y <= sqr.posY+sqr.sizeY))
        //  std::cout << '#';
        if (y == 0 && x <= 6) {}
        else if (drawChar(Char_ball, static_cast<int>(sqr.posX-sqr.sizeX), static_cast<int>(sqr.posY-sqr.sizeY), x, y)) {}

        else if ((sqr.speedX > 0 && x >= windowSize.ws_col - rightPl.width && y == pred.pred) || (sqr.speedX < 0 && x < leftPl.width && y == pred.pred)) 
          std::cout << "\x1B[36mX\033[0m";

        else if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) || 
            (x >= windowSize.ws_col - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height)))
          std::cout << '@';

        else if (drawChar(Char_colon, static_cast<int>(windowSize.ws_col/2) - 2, 1, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(leftPl.score + 1), static_cast<int>(windowSize.ws_col/2) - 6, 1, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(rightPl.score + 1), static_cast<int>(windowSize.ws_col/2) + 2, 1, x, y)) {}

        //else if (std::find(pred.pathX.begin(), pred.pathX.end(), x) != pred.pathX.end() && std::find(pred.pathY.begin(), pred.pathY.end(), y) != pred.pathY.end()) 
        else if (pathFind(pred, x, y)) 
          std::cout << "\033[0;33mx\033[0m";

        else std::cout << BACKGROUND_CHAR;

      }
      std::cout << std::endl;
    }
    //========================== Отрисовка ==========================//

    sleep_for(nanoseconds(30*1000000));

    fpsEndTime = std::chrono::high_resolution_clock::now();
    fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsEndTime - fpsStartTime );

    if (DEBUG) {
      // ОТЛАДОЧНУЮ ИНОРМАЦИЮ ПОМЕЩАТЬ СЮДА!
      
      char ch = getchar();
      if (ch == 'q') return 0;
      else if (ch == 'c') system("clear");
    }

  }
  return 0;
}

inline bool pathFind(prediction pred, int x, int y) {
  for (int i=0; i < pred.pathX.size(); i++) {
    if (pred.pathX[i] == x && pred.pathY[i] == y) return 1;
  }
  return 0;
}

void playerWinScreen (int player, winsize windowSize) {
  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds
                               
  system("clear");
  sleep_for(nanoseconds(500*1000000));

  int centerScrX = static_cast<int>(windowSize.ws_col / 2);
  int centerScrY = static_cast<int>(windowSize.ws_row / 2) - 3;

  for (int y = 0; y < windowSize.ws_row; y++){    
      for (int x = 0; x < windowSize.ws_col; x++){
             if (drawChar(Char_P, centerScrX-32, centerScrY, x, y)) {}
        else if (drawChar(Char_L, centerScrX-27, centerScrY, x, y)) {}
        else if (drawChar(Char_A, centerScrX-22, centerScrY, x, y)) {}
        else if (drawChar(Char_Y, centerScrX-17, centerScrY, x, y)) {}
        else if (drawChar(Char_E, centerScrX-12, centerScrY, x, y)) {}
        else if (drawChar(Char_R, centerScrX-7, centerScrY, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(player + 1), centerScrX+2, centerScrY, x, y)) {}
        else if (drawChar(Char_W, centerScrX+10, centerScrY+1, x, y)) {}
        else if (drawChar(Char_I, centerScrX+16, centerScrY, x, y)) {}
        else if (drawChar(Char_N, centerScrX+21, centerScrY, x, y)) {}
        else std::cout << BACKGROUND_CHAR;
      }
      std::cout << std::endl;
  }
  sleep_for(nanoseconds(2000*1000000));
  exit(0);
}

void newPointPlayer(int player, winsize windowSize) {
  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds
  
  system("clear");
  sleep_for(nanoseconds(500*1000000));

  int centerScrX = static_cast<int>(windowSize.ws_col / 2);
  int centerScrY = static_cast<int>(windowSize.ws_row / 2) - 3;

  for (int y = 0; y < windowSize.ws_row; y++){    
      for (int x = 0; x < windowSize.ws_col; x++){
             if (drawChar(Char_P, centerScrX-35, centerScrY, x, y)) {}
        else if (drawChar(Char_L, centerScrX-30, centerScrY, x, y)) {}
        else if (drawChar(Char_A, centerScrX-25, centerScrY, x, y)) {}
        else if (drawChar(Char_Y, centerScrX-20, centerScrY, x, y)) {}
        else if (drawChar(Char_E, centerScrX-15, centerScrY, x, y)) {}
        else if (drawChar(Char_R, centerScrX-10, centerScrY, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(player + 1), centerScrX-2, centerScrY, x, y)) {}
        else if (drawChar(Char_plus, centerScrX+8, centerScrY, x, y)) {}
        else if (drawChar(Char_1, centerScrX+15, centerScrY, x, y)) {}
        else if (drawChar(Char_P, centerScrX+25, centerScrY, x, y)) {}
        else if (drawChar(Char_O, centerScrX+30, centerScrY, x, y)) {}
        else if (drawChar(Char_I, centerScrX+35, centerScrY, x, y)) {}
        else if (drawChar(Char_N, centerScrX+40, centerScrY, x, y)) {}
        else if (drawChar(Char_T, centerScrX+45, centerScrY, x, y)) {}
        else std::cout << BACKGROUND_CHAR;
      }
      std::cout << std::endl;
  }
  sleep_for(nanoseconds(2000*1000000));
  //getchar();
}

bool drawChar (enum charsEnum chEn, int posX, int posY, int x, int y) {
  char outCh = ' ';
  int width=0, height=0;
  getSizeCh(chEn, width, height);
  //std::cerr << chEn << ' ' << width << ' ' << height << std::endl;
  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    outCh = getSymbolCh (chEn, x - posX, y - posY);
    if (outCh != ' ') {
      std::cout << outCh;
      return true;
    }
  }
  return false;
}

prediction calcPred(square sqrPred, int leftMargin, int rightMargin, winsize windowSize) {
  prediction pred = {0, 0};

  while (1) {
    if (sqrPred.posX + sqrPred.sizeX >= windowSize.ws_col - rightMargin - 1 && sqrPred.speedX > 0) break;
    else if (sqrPred.posX - sqrPred.sizeX <= leftMargin && sqrPred.speedX < 0) break;

    pred.predTime++;
    pred.pathX.push_back(static_cast<int>(sqrPred.posX));
    pred.pathY.push_back(static_cast<int>(sqrPred.posY));

    sqrPred.posX += sqrPred.speedX;
    sqrPred.posY += sqrPred.speedY;

    if (sqrPred.posY - sqrPred.sizeY <= 0)sqrPred.speedY *= -1;
    else if (sqrPred.posY + sqrPred.sizeY >= windowSize.ws_row-1)sqrPred.speedY *= -1;
  }  

  pred.pred = sqrPred.posY;
  return pred;
}

