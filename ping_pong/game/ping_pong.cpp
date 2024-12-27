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

#include <termios.h>
#include <fcntl.h>

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


void start_menu(int& pl1_var, int& pl2_var) {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  const short contentYsize = 4;
  system("clear");
  std::cout << "Составьте конфигурацию:" << std::endl;
  std::cout << std::setw(20) << std::left << "Player 1(left)" << std::setw(20) << "Player 2(right)" << std::endl;
  std::cout << std::setw(20) << std::left << "[*] bot"        << std::setw(20) << "[*] bot"         << std::endl;
  std::cout << std::setw(20) << std::left << "[ ] keyboard"   << std::setw(20) << "[ ] keyboard"    << std::endl;
  std::cout << std::setw(20) << std::left << "[ ] std"        << std::setw(20) << "[ ] std"         << std::endl;
  std::cout << std::setw(20) << std::left << "[ ] http"       << std::setw(20) << "[ ] http"        << std::endl;
  std::cout << std::endl <<  "Используйте h(<) j(v) k(^) l(>) для перемещения\n\tи _ (пробел) для выбора пункта" << std::endl;
  std::cout << "Для выхода из меню используйте Enter,\n\tа для выхода из игры - q" << std::endl;

  //int pl1_var=0, pl2_var=0;
  pl1_var=0; pl2_var=0;

  int x=0, y=0;
  std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H';

  char ch;
  while ((ch = getchar()) != '\n') {
    switch(ch) {
      case 'h': 
        if (--x < 0) x = 0;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'j': 
        if (++y > contentYsize - 1) y = contentYsize - 1;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'k': 
        if (--y < 0) y = 0;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'l': 
        if (++x > 1) x = 1;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case ' ':
        if (x == 0) {
          std::cout << "\033[" << pl1_var+3 << ';' << 2 << 'H' << ' ';
          pl1_var = y;
          std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << '*'
            << "\033[" << y+3 << ';' << x*20+2 << 'H';
        } else {
          std::cout << "\033[" << pl2_var+3 << ';' << 22 << 'H' << ' ';
          pl2_var = y;
          std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << '*'
            << "\033[" << y+3 << ';' << x*20+2 << 'H';
        }
        break;

      case 'q': 
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
        fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags
        std::cout << "\033[" << contentYsize + 3+6 << ';' << 0 << 'H' << std::endl;
        exit(0); break;

      default:
        std::cout << "\033[" << contentYsize + 3+5 << ';' << 0 << 'H' << "Command \'" << ch << "\' not found"
                  << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
  fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags
}

int main(int argc, char const *argv[]) {
  //struct termios newt;
  //tcgetattr(STDIN_FILENO, &newt);
  //newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
  //tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int pl1_mode=0, pl2_mode=0;
  start_menu(pl1_mode, pl2_mode);

  using namespace std::this_thread; // sleep_for, sleep_until
  using namespace std::chrono; // nanoseconds, system_clock, seconds

  struct winsize windowSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
  windowSize.ws_row -= 1;

  int sock;
  if (pl1_mode == http_pl_mode || pl2_mode == http_pl_mode) {
    initSocket(sock);
  }

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
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        rightPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
    }
    else if (sqr.posX + sqr.sizeX >= windowSize.ws_col - rightPl.width - 1) {
      sqr.speedX *= -1;
      if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
        newPointPlayer(1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        leftPl.score++;
        sqr = defaultSqr;
      }

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
    }


    if (leftPl.score >= 3) {
      playerWinScreen (1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      exit(0);
    } else if (rightPl.score >= 3) {
      playerWinScreen (2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
      exit(0);
    }


    switch(pl1_mode){
      case bot_pl_mode:
        leftPl.showPred = true;
        botTick(leftPl, sqr, pred, windowSize.ws_col, windowSize.ws_row);
        break;
      case keyboard_pl_mode:
        leftPl.showPred = false;
        keyInpTick (leftPl, 'a', 'z', windowSize.ws_col, windowSize.ws_row);
        break;
      case std_pl_mode:
        leftPl.showPred = false;
        serial_stdTick (leftPl, 'a', 'z', windowSize.ws_col, windowSize.ws_row);
        break;
      case http_pl_mode:
        leftPl.showPred = false;
        getHttpBtnCout(sock, leftPl, windowSize.ws_col, windowSize.ws_row);
        break;
    }

    switch(pl2_mode){
      case bot_pl_mode:
        rightPl.showPred = true;
        botTick(rightPl, sqr, pred, windowSize.ws_col, windowSize.ws_row);
        break;
      case keyboard_pl_mode:
        rightPl.showPred = false;
        keyInpTick (rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
        break;
      case std_pl_mode:
        rightPl.showPred = false;
        serial_stdTick (rightPl, '\'', '/', windowSize.ws_col, windowSize.ws_row);
        break;
      case http_pl_mode:
        rightPl.showPred = false;
        getHttpBtnCout(sock, rightPl, windowSize.ws_col, windowSize.ws_row);
        break;
    }

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

