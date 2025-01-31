#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "config_menu.h"

void start_menu(enum mode_joy& joy_md, int windowWidth, int windowHeight) {

  struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  const unsigned short contentYsize = 3;

  for (int i = 0; i < windowHeight*2; i++)
    std::cout << std::endl;
  std::cout << "\033[1;1H";

  std::cout << "Составьте конфигурацию:" << std::endl
    << " [*] joy" << std::endl
    << " [ ] game (ps) joy" << std::endl
    << " [ ] rudder" << std::endl;

  std::cout << std::endl <<  "Используйте стрелки или h(<) j(v) k(^) l(>) для перемещения\n\tи _ (пробел) для выбора пункта" << std::endl;
  std::cout << "Для выхода из меню(старта программы) используйте Enter,\n\tа для выхода полностью - q" << std::endl;

  std::cout << "\033[2;3H";

  int y=0;

  char ch;
  while ((ch = getchar()) != '\n') {
    switch (ch) {
      case 'B':
      case 'j':
        if (++y > contentYsize - 1) y = contentYsize - 1;
        std::cout << "\033[" << y+2 << ";3H"; break;
      case 'A':
      case 'k':
        if (--y < 0) y = 0;
        std::cout << "\033[" << y+2 << ";3H"; break;
      case ' ':
        std::cout << "\033[" << joy_md+2 << ";3H ";
        std::cout << "\033[" << y+2 << ";3H*"
          << "\033[" << y+2 << ";3H";

        joy_md = static_cast<mode_joy>(y);
        break;

      case 'q':
      case 'Q':
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        std::cout << "\033[" << contentYsize + 2+6 << ';' << 0 << 'H' << std::endl;
        exit(0); break;
    }
  }
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
  fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags
}

