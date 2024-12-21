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

#include "include/assets.h"
#include "include/inputs.h"
#include "include/draw.h"

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


int main(int argc, char const *argv[]) {
  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

  struct winsize windowSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
  windowSize.ws_row -= 1;

#if defined(PL1_HTTP) || defined(PL2_HTTP)
  int sock;
  initSocket(sock);
#endif

  auto fpsStartTime = std::chrono::high_resolution_clock::now(), fpsEndTime = std::chrono::high_resolution_clock::now();
  auto fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsStartTime - fpsEndTime);
  std::vector<int> fps_vector = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  const square defaultSqr = {static_cast<float>(windowSize.ws_col/2), static_cast<float>(windowSize.ws_row/2), 1, 0.5F, 4, 2};
  square sqr = defaultSqr;

  player leftPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};
  player rightPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10};

  prediction pred;

  pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);

  while(1){

    fpsStartTime = std::chrono::high_resolution_clock::now();

    sqr.posX += sqr.speedX;
    sqr.posY += sqr.speedY;

    pred.pathX.erase(pred.pathX.begin());
    pred.pathY.erase(pred.pathY.begin());


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
    }


    if (leftPl.score >= 3) {
      playerWinScreen (1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      sleep_for(nanoseconds(2000*1000000));
      exit(0);
    } else if (rightPl.score >= 3) {
      playerWinScreen (2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      sleep_for(nanoseconds(2000*1000000));
      exit(0);
    }


    #ifdef PL1_BOT
      leftPl.showPred = true;
      botTick(leftPl,  sqr, pred, windowSize.ws_col, windowSize.ws_row);
    #elif PL1_KEYBOARD
      leftPl.showPred = false;
      keyInpTick (leftPl,  'a',  'z', windowSize.ws_col, windowSize.ws_row);
    #elif Pl1_STD
      leftPl.showPred = false;
      serial_stdTick (leftPl,  'a',  'z', windowSize.ws_col, windowSize.ws_row);
    #elif PL1_HTTP
      leftPl.showPred = false;
      getHttpBtnCout(sock, leftPl, windowSize.ws_col, windowSize.ws_row);
    #else
      #error use -DPL1_[BOT/KEYBOARD/STD/HTTP]
    #endif

    #ifdef PL2_BOT
      rightPl.showPred = true;
      botTick(rightPl, sqr, pred, windowSize.ws_col, windowSize.ws_row);
    #elif PL2_KEYBOARD
      rightPl.showPred = false;
      keyInpTick (rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
    #elif Pl2_STD
      rightPl.showPred = false;
      serial_stdTick (rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
    #elif PL2_HTTP
      rightPl.showPred = false;
      getHttpBtnCout(sock, rightPl, windowSize.ws_col, windowSize.ws_row);
    #else
      #error use -DPL2_[BOT/KEYBOARD/STD/HTTP]
    #endif

    pred.predTime--;

    int fpsCount = (fpsFrameTime.count() == 0) ? 0 : static_cast<int>(1000/fpsFrameTime.count());
    fps_vector.push_back(fpsCount);
    fps_vector.erase(fps_vector.begin());
    int meanFps = static_cast<int> (accumulate(fps_vector.begin(), fps_vector.end(), 0) / fps_vector.size());

    drawScreen(sqr, rightPl, leftPl, windowSize.ws_col, windowSize.ws_row, meanFps, BACKGROUND_CHAR, pred);

    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    fpsEndTime = std::chrono::high_resolution_clock::now();
    fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsEndTime - fpsStartTime );

#if DEBUG
    char ch = getchar();
    if (ch == 'q') return 0;
    else if (ch == 'c') system("clear");
#endif

  }
  return 0;
}

