#include "include/assets.h"
#include <iostream>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

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

void serial_stdTick(player &pl, int windowWidth, int windowHeight) {
    static bool isStartNums;

    char InpChar;
    while (!isStartNums) {
        std::cin >> InpChar;
        if (InpChar == '$')
            isStartNums = true;
    }

    std::vector<char> buffer;

    while (kbhit_std()) {
        std::cin >> InpChar;

        if (InpChar == pl.up_key)
            pl.pos--;
        else if (InpChar == pl.down_key)
            pl.pos++;
        else
            buffer.push_back(InpChar);
    }

    for (int i = 0; i < static_cast<int>(buffer.size()); i++) {
        ungetc(buffer[i], stdin);
    }

    if (pl.pos < 0)
        pl.pos = 0;
    else if (pl.pos + pl.height > windowHeight)
        pl.pos = windowHeight - pl.height;
}
