#include "include/assets.h"
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <utility>
#include <vector>

std::pair<bool, char> kbhit() {
    std::pair<bool, char> result;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK); // Set non-blocking mode

    int ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // Restore old terminal settings
    fcntl(STDIN_FILENO, F_SETFL, oldf);      // Restore old flags

    if (ch == EOF) {
        result.first = false;
    } else {
        result.first = true;
        result.second = ch;
    }
    return (result);
}

void keyInpTick(player &pl, int windowWidth, int windowHeight) {
    std::vector<char> buffer;
    std::pair<bool, char> p;

    do {
        p = kbhit();
        if (p.first) {
            if (p.second == pl.up_key)
                pl.pos--;
            else if (p.second == pl.down_key)
                pl.pos++;
            else
                buffer.push_back(p.second);
        }
    } while (p.first);

    for (int i = 0; i < static_cast<int>(buffer.size()); i++) {
        ungetc(buffer[i], stdin);
    }

    if (pl.pos < 0)
        pl.pos = 0;
    else if (pl.pos + pl.height > windowHeight)
        pl.pos = windowHeight - pl.height;
}
