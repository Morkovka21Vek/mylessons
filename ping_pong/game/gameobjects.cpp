#include "gameobjects.hpp"
#include "assets.hpp"
#include <iostream>
#include <vector>

ball::ball(float _speedX, float _speedY, int _width, int _height)
    : posX(-1), posY(-1), width(_width), height(_height),
      default_speedX(_speedX), default_speedY(_speedY) {}
void ball::tick(struct scrsize ws, size_t frametime) {
    if (this->posX == -1 || this->posY == -1) {
        this->reset(ws);
    }

    this->posX += this->speedX * frametime;
    this->posY += this->speedY * frametime;

    if (this->posY <= 0)
        this->speedY = -this->speedY;
    else if (this->posY + this->height >= ws.height)
        this->speedY = -this->speedY;

    if (this->posX <= 0)
        this->speedX = -this->speedX;
    else if (this->posX + this->width >= ws.width)
        this->speedX = -this->speedX;
}

void ball::reset(struct scrsize ws) {
    this->posX = ws.width / 2;
    this->posY = ws.height / 2;

    this->speedX = this->default_speedX;
    this->speedY = this->default_speedY;
}

float ball::getX() const { return this->posX; }
float ball::getY() const { return this->posY; }

std::vector<std::vector<char>> ball::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}

player::player(int _width, int _height, enum playermode _mode, enum playerpos _posX)
    : pos(-1), score(0), width(_width), height(_height), mode(_mode), posX(_posX) {}

bool player::tick(struct scrsize ws, ball bl) {
    using enum playermode;

    if (this->pos == -1) {
        this->reset(ws);
    }

    int temppos = 0;
    switch (this->mode) {
    case bot:
        temppos = this->bot(bl.getY());
    }
    temppos = (temppos < 0) ? 0 : temppos;
    this->pos = (temppos + this->height >= ws.height)
                    ? ws.height - this->height - 1
                    : temppos;

    return false;
}

int player::getScore() const { return this->score; }

int player::getPos() const { return this->pos; }

size_t player::calcX(struct scrsize ws) const {
    return (this->posX == playerpos::left) ? 0 : ws.width - this->width;
}

void player::reset(struct scrsize ws) {
    this->pos = (ws.height - this->height) / 2;
}

std::vector<std::vector<char>> player::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
