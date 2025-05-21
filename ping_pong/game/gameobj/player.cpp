#include "gameobj/player.hpp"
#include "assets.hpp"
#include <vector>

Player::Player(int _width, int _height, enum Playermode _mode,
               enum Playerpos _posX)
    : width(_width), height(_height), mode(_mode), posX(_posX) {}

void Player::tick(struct scrsize ws, float ballPosY) {
    using enum Playermode;

    if (this->pos == -1) {
        this->reset(ws);
    }

    switch (this->mode) {
    case bot:
        this->pos = correctPos(this->bot(ballPosY), ws);
        break;
    case keyboard:
        this->pos = correctPos(this->keyboard(), ws);
        break;
    }
}

int Player::correctPos(int val, const scrsize ws) const {
    val = (val < 0) ? 0 : val;
    return (val + this->height > ws.height) ? ws.height - this->height : val;
}

int Player::getPos() const { return this->pos; }

size_t Player::calcX(struct scrsize ws) const {
    return (this->posX == Playerpos::left) ? 0 : ws.width - this->width;
}

size_t Player::getWidth() const { return this->width; }
size_t Player::getHeight() const { return this->height; }

Playerpos Player::getPlayerposX() const { return this->posX; }

void Player::reset(struct scrsize ws) {
    this->pos = (ws.height - this->height) / 2;
}

std::vector<std::vector<char>> Player::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
