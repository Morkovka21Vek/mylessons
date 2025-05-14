#include "gameobj/player.hpp"

int player::bot(float posY) const { return posY - this->height / 2; }
