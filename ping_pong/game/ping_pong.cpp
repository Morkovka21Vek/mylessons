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
#include <termios.h>
#include <fcntl.h>

#include "include/assets.h"
#include "include/inputs.h"
#include "include/draw.h"

#ifndef BACKCHAR
  #define BACKGROUND_CHAR '-'
#else
  #define BACKGROUND_CHAR BACKCHAR
#endif

void start_menu(player& leftPl, player& rightPl, int windowWidth, int windowHeight) {
  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  const unsigned short contentYsize_default = 4;
  unsigned short contentYsize = contentYsize_default;

  for (int i = 0; i < windowHeight * 2; i++)
    std::cout << std::endl;
  std::cout << "\033[1;1H";

  std::cout << std::left << "Составьте конфигурацию:" << std::endl
            << std::setw(20) << "Player 1(left)" << std::setw(20) << "Player 2(right)" << std::endl
            << std::setw(20) << "[*] bot"        << std::setw(20) << "[*] bot"         << std::endl
            << std::setw(20) << "[ ] keyboard"   << std::setw(20) << "[ ] keyboard"    << std::endl
            << std::setw(20) << "[ ] std"        << std::setw(20) << "[ ] std"         << std::endl
            << std::setw(20) << "[ ] http"       << std::setw(20) << "[ ] http"        << std::endl;

  std::cout << std::endl <<  "Используйте стрелки или h(<) j(v) k(^) l(>) для перемещения\n\tи _ (пробел) для выбора пункта" << std::endl;
  std::cout << "Для выхода из меню используйте Enter,\n\tа для выхода из игры - q" << std::endl;

  int x=0, y=0;
  std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H';

  char ch;
  while ((ch = getchar()) != '\n') {
    switch (ch) {
      case 'D':
      case 'h':
        if (--x < 0) x = 0;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'B':
      case 'j':
        if (++y > contentYsize - 1) y = contentYsize - 1;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'A':
      case 'k':
        if (--y < 0) y = 0;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case 'C':
      case 'l':
        if (++x > 1) x = 1;
        std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H'; break;
      case ' ':
        if (x == 0) {
          std::cout << "\033[" << leftPl.mode+3 << ';' << 2 << 'H' << ' ';
          leftPl.mode = y;
          std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << '*'
            << "\033[" << y+3 << ';' << x*20+2 << 'H';
        } else {
          std::cout << "\033[" << rightPl.mode+3 << ';' << 22 << 'H' << ' ';
          rightPl.mode = y;
          std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << '*'
            << "\033[" << y+3 << ';' << x*20+2 << 'H';
        }
        break;

      case 'q':
      case 'Q':
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
        fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags
        std::cout << "\033[" << contentYsize + 3+6 << ';' << 0 << 'H' << std::endl;
        exit(0); break;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
  fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags
}

int main(int argc, char const *argv[]) {
  using namespace std::chrono;

  struct winsize windowSize;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &windowSize);
  windowSize.ws_row -= 1;

  player leftPl  = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10, false, 0, 'a',  'z'};
  player rightPl = {static_cast<int>(windowSize.ws_row/2), 0, 4, 10, false, 0, '\'', '/'};

  start_menu(leftPl, rightPl, windowSize.ws_col, windowSize.ws_row);

  int sock;
  if (leftPl.mode == http_pl_mode || rightPl.mode == http_pl_mode) {
    initSocket(sock);
  }

  auto fpsStartTime = std::chrono::high_resolution_clock::now(), fpsEndTime = std::chrono::high_resolution_clock::now();
  auto fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsStartTime - fpsEndTime);
  std::vector<int> fps_vector = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  bool redrawing_screen = true;

  const square defaultSqr = {static_cast<float>(windowSize.ws_col/2), static_cast<float>(windowSize.ws_row/2), 1, 0.5F, 4, 2};
  square sqr = defaultSqr;


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
      if (!(sqr.posY + sqr.sizeY >= leftPl.pos && sqr.posY - sqr.sizeY < leftPl.pos + leftPl.height)) {
        if (sqr.posX - sqr.sizeX <= 0) {
          newPointPlayer(2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
          std::this_thread::sleep_for(std::chrono::milliseconds(2000));
          rightPl.score++;
          rightPl.pos = static_cast<int>(windowSize.ws_row/2);
          leftPl.pos  = static_cast<int>(windowSize.ws_row/2);
          sqr = defaultSqr;
          redrawing_screen = true;
        }
      } else
        sqr.speedX = (sqr.speedX > 0) ? sqr.speedX : -sqr.speedX;


      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
    }
    else if (sqr.posX + sqr.sizeX >= windowSize.ws_col - rightPl.width - 1) {
      if (!(sqr.posY + sqr.sizeY >= rightPl.pos && sqr.posY - sqr.sizeY < rightPl.pos + rightPl.height)) {
        if (sqr.posX + sqr.sizeX >= windowSize.ws_col - 1) {
          newPointPlayer(1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
          std::this_thread::sleep_for(std::chrono::milliseconds(2000));
          leftPl.score++;
          rightPl.pos = static_cast<int>(windowSize.ws_row/2);
          leftPl.pos  = static_cast<int>(windowSize.ws_row/2);
          sqr = defaultSqr;
          redrawing_screen = true;
        }
      }
      else
        sqr.speedX = (sqr.speedX < 0) ? sqr.speedX : -sqr.speedX;

      pred = calcPred(sqr, leftPl.width, rightPl.width, windowSize.ws_col, windowSize.ws_row);
    }


    if (leftPl.score >= 3) {
      playerWinScreen (1, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      exit(0);
    } else if (rightPl.score >= 3) {
      playerWinScreen (2, windowSize.ws_col, windowSize.ws_row, BACKGROUND_CHAR);
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      exit(0);
    }


    switch(leftPl.mode){
      case bot_pl_mode:
        leftPl.showPred = true;
        botTick(leftPl, sqr, pred, windowSize.ws_col, windowSize.ws_row);
        break;
      case keyboard_pl_mode:
        leftPl.showPred = false;
        keyInpTick (leftPl, windowSize.ws_col, windowSize.ws_row);
        break;
      case std_pl_mode:
        leftPl.showPred = false;
        serial_stdTick (leftPl, windowSize.ws_col, windowSize.ws_row);
        break;
      case http_pl_mode:
        leftPl.showPred = false;
        getHttpBtnCout(sock, leftPl, windowSize.ws_col, windowSize.ws_row);
        break;
    }

    switch(rightPl.mode){
      case bot_pl_mode:
        rightPl.showPred = true;
        botTick(rightPl, sqr, pred, windowSize.ws_col, windowSize.ws_row);
        break;
      case keyboard_pl_mode:
        rightPl.showPred = false;
        keyInpTick (rightPl, windowSize.ws_col, windowSize.ws_row);
        break;
      case std_pl_mode:
        rightPl.showPred = false;
        serial_stdTick (rightPl, windowSize.ws_col, windowSize.ws_row);
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

    drawScreen(sqr, rightPl, leftPl, windowSize.ws_col, windowSize.ws_row, meanFps, BACKGROUND_CHAR, pred, redrawing_screen);

    std::vector<char> buffer_stdin;
    std::pair<bool,char> p;
    do{
      p = kbhit();
      if (p.first){
        switch(p.second) {
          case '\n':
          case 'c':
          case 'C':
            redrawing_screen = true;
            break;
          case 'q':
          case 'Q':
            return 0;
            break;
          default:
            buffer_stdin.push_back(p.second);
            break;
        }
      }
    } while(p.first);

    for (int i=0; i < static_cast<int>(buffer_stdin.size()); i++) {
      ungetc(buffer_stdin[i], stdin);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    fpsEndTime = std::chrono::high_resolution_clock::now();
    fpsFrameTime = duration_cast<std::chrono::milliseconds> (fpsEndTime - fpsStartTime);
  }
  return 0;
}

