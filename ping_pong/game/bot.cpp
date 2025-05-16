#include "gameobj/player.hpp"

int Player::bot(float posY) const { return posY - this->height / 2; }
