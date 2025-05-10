#include "gameobjects.hpp"
#include "assets.hpp"
#include <iostream>

ball::ball(float _speedX, float _speedY, int _sizeX, int _sizeY)
    : posX(-1), posY(-1), sizeX(_sizeX), sizeY(_sizeY), default_speedX(_speedX),
      default_speedY(_speedY) {}
void ball::tick(struct scrsize ws, size_t frametime) {
    if (this->posX == -1 || this->posY == -1) {
        this->reset(ws);
    }

    this->posX += this->speedX * frametime;
    this->posY += this->speedY * frametime;

    if (this->posY <= 0)
        this->speedY = -this->speedY;
    else if (this->posY + this->sizeY >= ws.height)
        this->speedY = -this->speedY;

    if (this->posX <= 0)
        this->speedX = -this->speedX;
    else if (this->posX + this->sizeX >= ws.width)
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

player::player(int _width, int _height, enum playermode _mode): pos(-1), score(0), width(_width), height(_height), mode(_mode)
{}

bool player::tick(struct scrsize ws, ball bl) {
    using enum playermode;

    if (this->pos == -1) {
        this->reset(ws);
    }

    int temppos = 0;
    switch(this->mode) {
        case bot: temppos = this->bot(bl.getY());
    }
    this->pos = (((temppos < 0)?0:temppos)+this->height >= ws.height)?ws.height:temppos;

    return false;
}

int player::getScore() const {
    return this->score;
}

void player::reset(struct scrsize ws) {
    this->pos = (ws.height - this->height)/2;
}
