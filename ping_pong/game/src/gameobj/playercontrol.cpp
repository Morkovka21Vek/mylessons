#include "gameobj/player.hpp"
#include <ncurses.h>

int Player::bot(float posY) const { return posY - static_cast<float>(size.height) / 2; }

int Player::keyboard() const {
    switch (getch()) {
    case 'a':
    case 'A':
        return pos - 1;
    case 'z':
    case 'Z':
        return pos + 1;
    default:
        return pos;
    }
}
