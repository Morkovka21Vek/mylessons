#include "assets.h"
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

bool isStartNums; 

bool kbhit_std() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int bytesWaiting = 0;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return bytesWaiting > 0;
}

void serial_stdTick (player& pl1, char up_key1, char down_key1, player& pl2, char up_key2, char down_key2, int windowWidth, int windowHeight) {
  char InpChar;
  while (!isStartNums) {
    std::cin >> InpChar;
    //std::cout << InpChar;
    if (InpChar == '$') 
      isStartNums = true;
  } 

  while(kbhit_std()){
    std::cin >> InpChar;
    if (InpChar == up_key1) pl1.pos--;
    else if (InpChar == down_key1) pl1.pos++;
    else if (InpChar == up_key2) pl2.pos--;
    else if (InpChar == down_key2) pl2.pos++;
  }

  if (pl1.pos < 0) pl1.pos = 0;
  else if (pl1.pos + pl1.height > windowHeight) pl1.pos = windowHeight - pl1.height;

  if (pl2.pos < 0) pl2.pos = 0;
  else if (pl2.pos + pl2.height > windowHeight) pl2.pos = windowHeight - pl2.height;
}

