#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "include/assets.h"

void set_curs_star(int x, int y, player& leftPl, player& rightPl, unsigned short contentYsize) {

  static bool pl1_change_pred = false, pl2_change_pred = false;
  player& pl = (x == 0) ? leftPl : rightPl;
  bool& change_pred = (x == 0) ? pl1_change_pred : pl2_change_pred;

  if (y == 4)
  {
    pl.showPred = !pl.showPred;
    change_pred = true;

    std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << ((pl.showPred) ? '*' : ' ')
      << "\033[" << y+3 << ';' << x*20+2 << 'H';
  }
  else
  {
    std::cout << "\033[" << pl.mode+3 << ';' << x*20+2 << 'H' << ' ';
    pl.mode = y;

    if (!change_pred && y == bot_pl_mode) {
      std::cout << "\033[" << contentYsize-1+3 << ';' << x*20+2 << 'H' << '*';
      pl.showPred = true;
    } else if (!change_pred) {
      std::cout << "\033[" << contentYsize-1+3 << ';' << x*20+2 << 'H' << ' ';
      pl.showPred = false;
    }

    std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H' << '*'
      << "\033[" << y+3 << ';' << x*20+2 << 'H';
  }
}

void start_menu(player& leftPl, player& rightPl, int windowWidth, int windowHeight) {

  const char* plmods[] = {
    "bot",
    "keyboard",
    "std",
    "http"
  };

  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  const unsigned short contentYsize_default = 5;
  unsigned short contentYsize = contentYsize_default;

  for (int i = 0; i < windowHeight * 2; i++)
    std::cout << std::endl;
  std::cout << "\033[1;1H";

  std::cout << std::left << "Составьте конфигурацию:" << std::endl
            << std::setw(20) << "Player 1(left)" << std::setw(20) << "Player 2(right)" << std::endl;

  for (unsigned int i = 0; i < static_cast<unsigned int>(sizeof(plmods) / sizeof(char*)); i++) {
    std::cout << "[ ] " << std::setw(16) << plmods[i] << "[ ] " << std::setw(16) << plmods[i] << std::endl;
  }

  std::cout << "\033[32m" << std::setw(20) << "[ ] pred" << std::setw(20) << "[ ] pred" << "\033[0m" << std::endl;

  std::cout << std::endl <<  "Используйте стрелки или h(<) j(v) k(^) l(>) для перемещения\n\tи _ (пробел) для выбора пункта" << std::endl;
  std::cout << "Для выхода из меню(продолжения игры) используйте Enter,\n\tа для выхода из игры - q" << std::endl;

  int x=0, y=0;
  set_curs_star(1, y, leftPl, rightPl, contentYsize);
  set_curs_star(0, y, leftPl, rightPl, contentYsize);
  //std::cout << "\033[" << y+3 << ';' << x*20+2 << 'H';

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
        set_curs_star(x, y, leftPl, rightPl, contentYsize);
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

