#include "gameobj/player.hpp"
#include <ncurses.h>

int Player::bot(float posY) const {
    return posY - static_cast<float>(this->height) / 2;
}

int Player::keyboard() const {
    int result = this->pos;

    switch (getch()) {
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
