#include "assets.hpp"
#include "gameobj/player.hpp"
#include <vector>

Player::Player(int _width, int _height, enum Playermode _mode, enum Playerpos _posX)
    : pos(-1), width(_width), height(_height), mode(_mode), posX(_posX) {}

void Player::tick(struct scrsize ws, float ball_posY) {
    using enum Playermode;

    if (this->pos == -1) {
        this->reset(ws);
    }

    int temppos = 0;
    switch (this->mode) {
    case bot:
        temppos = this->bot(ball_posY);
    }
    temppos = (temppos < 0) ? 0 : temppos;
    this->pos = (temppos + this->height > ws.height)
                    ? ws.height - this->height
                    : temppos;
}

int Player::getPos() const { return this->pos; }

size_t Player::calcX(struct scrsize ws) const {
    return (this->posX == Playerpos::left) ? 0 : ws.width - this->width;
}

size_t Player::getWidth() const { return this->width; }
size_t Player::getHeight() const { return this->height; }

Playerpos Player::getPlPosX() const {
    return this->posX;
}

void Player::reset(struct scrsize ws) {
    this->pos = (ws.height - this->height) / 2;
}

std::vector<std::vector<char>> Player::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
