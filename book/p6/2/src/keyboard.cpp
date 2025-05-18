#include "keyboard.hpp"
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
