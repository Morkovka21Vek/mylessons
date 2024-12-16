#include "include/assets.h"
#include <utility>
#include <termios.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>


std::pair<bool,char> kbhit() {
    std::pair<bool,char> result;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // Set non-blocking mode

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
    fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags

    if (ch == EOF) {
      result.first = false;
    }
    else {
        result.first = true;
        result.second = ch;
    }
    return (result);
}

void keyInpTick (player& pl1, char up_key1, char down_key1, player& pl2, char up_key2, char down_key2, int windowWidth, int windowHeight) {
  std::pair<bool,char> p;
  do{
    p = kbhit();
    if (p.first){
      if (p.second == up_key1) pl1.pos--;
      else if (p.second == down_key1) pl1.pos++;
      else if (p.second == up_key2) pl2.pos--;
      else if (p.second == down_key2) pl2.pos++;
    }
  } while(p.first);
  if (pl1.pos < 0) pl1.pos = 0;
  else if (pl1.pos + pl1.height > windowHeight) pl1.pos = windowHeight - pl1.height;

  if (pl2.pos < 0) pl2.pos = 0;
  else if (pl2.pos + pl2.height > windowHeight) pl2.pos = windowHeight - pl2.height;
}

