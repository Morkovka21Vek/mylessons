#include "keyboard.hpp"
#include <termios.h>
#include <fcntl.h>
#include <iostream>
#include <unistd.h>

char kbhit() {
    std::pair<bool,char> result;
    struct termios oldt;
    struct termios newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // Set non-blocking mode

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
    fcntl(STDIN_FILENO, F_SETFL, oldf); // Restore old flags

    return ch;
}
