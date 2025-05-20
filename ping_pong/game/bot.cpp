#include "gameobj/player.hpp"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

int Player::bot(float posY) const { return posY - this->height / 2; }

int kbhit();

int Player::keyboard() const {
    int result = this->pos;

    switch (kbhit()) {
        case 'a':
        case 'A':
            result--;
            break;
        case 'z':
        case 'Z':
            result++;
            break;
        default:
            break;
    }

    return result;
}

int kbhit() {
    struct termios oldt;
    struct termios newt;
    int ch;
    int oldf;

    if (tcgetattr(STDIN_FILENO, &oldt) < 0) {
        return EOF;
    }

    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // Disable canonical mode and echo
    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) < 0) {
        return EOF;
    }

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    if (oldf == -1) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return EOF;
    }

    if (fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK) == -1) {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return EOF;
    }

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return ch;
}
