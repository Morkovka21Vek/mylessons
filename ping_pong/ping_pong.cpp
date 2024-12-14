/*    _             __  __            _              _         ____  ___     __   _
 *   | |__  _   _  |  \/  | ___  _ __| | _______   _| | ____ _|___ \/ \ \   / /__| | __
 *   | '_ \| | | | | |\/| |/ _ \| '__| |/ / _ \ \ / / |/ / _` | __) | |\ \ / / _ \ |/ /
 *   | |_) | |_| | | |  | | (_) | |  |   < (_) \ V /|   < (_| |/ __/| | \ V /  __/   <
 *   |_.__/ \__, | |_|  |_|\___/|_|  |_|\_\___/ \_/ |_|\_\__,_|_____|_|  \_/ \___|_|\_\
 *          |___/
 */

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
#include <vector>
#include <algorithm>

#include "assets.h"
#include "inputs.h"
#include "draw.h"

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

  const square defaultSqr = {static_cast<float>(windowSize.ws_col/2), static_cast<float>(windowSize.ws_row/2), 1, 0.5F, 4, 2};
  square sqr = defaultSqr;

  player leftPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};
  player rightPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};

  prediction pred;

  //========================== Инциализация переменных ==========================//

  //auto movePlRand = std::bind(std::uniform_int_distribution<>(-3,3),std::default_random_engine());
  //auto winPlRand = std::bind(std::uniform_int_distribution<>(0,2),std::default_random_engine());

  pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);

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
        newPointPlayer(2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
        sleep_for(nanoseconds(2000*1000000));
        rightPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
      //plWin = winPlRand();
    }
    else if (sqr.posX + sqr.sizeX >= windowSize.ws_col - rightPl.width - 1) {
      sqr.speedX *= -1;
      if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
        newPointPlayer(1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
        sleep_for(nanoseconds(2000*1000000));
        leftPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
      //plWin = winPlRand();
    }

    //========================== Проверка на столкновения ==========================//

    if (leftPl.score >= 3) {
      playerWinScreen (1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      sleep_for(nanoseconds(2000*1000000));
      exit(0);
    } else if (rightPl.score >= 3) {
      playerWinScreen (2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      sleep_for(nanoseconds(2000*1000000));
      exit(0);
    }


    //========================== Изменение положения и проверка игрока ==========================//
    #ifdef BOT
      botTick(leftPl, sqr, windowSize.ws_col, windowSize.ws_row);
      botTick(rightPl, sqr, windowSize.ws_col, windowSize.ws_row);
    #elif KEYBOARD
      keyInpTick (leftPl, 'a', 'z', rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
    #elif STD
      serial_stdTick (leftPl, 'a', 'z', rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
    #elif HTTP
      getHttpBtnCout(leftPl, rightPl, windowSize.ws_col, windowSize.ws_row);
    #else
      #error use -D[BOT/KEYBOARD/STD/HTTP]
    #endif

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
      char ch = getchar();
      if (ch == 'q') return 0;
      else if (ch == 'c') system("clear");
    }

  }
  return 0;
}

inline bool pathFind(prediction pred, int x, int y) {
  for (int i=0; i < static_cast<int>(pred.pathX.size()); i++) {
    if (pred.pathX[i] == x && pred.pathY[i] == y) return 1;
  }
  return 0;
}

