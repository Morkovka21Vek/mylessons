#include "gameobj/player.hpp"
#include <vector>
#include "assets.hpp"

Player::Player(size_t width, size_t height, enum Playermode mode,
               enum PlayerSide side)
    : size(width, height), mode(mode), side(side) {}
Player::Player(Size2D size, enum Playermode mode,
               enum PlayerSide side)
    : size(size), mode(mode), side(side) {}

void Player::tick(Size2D ws, float ballPosY) {
    switch (this->mode) {
    case Playermode::bot:
        this->pos = correctPos(this->bot(ballPosY), ws);
        break;
    case Playermode::keyboard:
        this->pos = correctPos(this->keyboard(), ws);
        break;
    }
}

int Player::correctPos(int val, Size2D ws) const {
    val = (val < 0) ? 0 : val;
    return (val + size.height > ws.height) ? ws.height - size.height : val;
}

int Player::getPos() const { return this->pos; }

int Player::calcX(Size2D ws) const {
    return (this->side == PlayerSide::left) ? 0 : ws.width - size.width;
}

Size2D Player::getSize() const { return size; }

PlayerSide Player::getSide() const { return side; }

void Player::reset(Size2D ws) {
    this->pos = (ws.height - size.height) / 2;
}

std::vector<std::vector<char>> Player::getMatrix() const {
    std::vector<std::vector<char>> matrix(size.height,
                                          std::vector<char>(size.width, '#'));
    return matrix;
}
