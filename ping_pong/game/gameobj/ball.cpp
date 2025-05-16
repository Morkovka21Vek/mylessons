#include "assets.hpp"
#include "gameobj/ball.hpp"
#include <vector>

Ball::Ball(float _speedX, float _speedY, int _width, int _height)
    : posX(-1), posY(-1), width(_width), height(_height),
      default_speedX(_speedX), default_speedY(_speedY) {}
void Ball::tick(struct scrsize ws, size_t frametime) {
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

void Ball::reset(struct scrsize ws) {
    this->posX = ws.width / 2;
    this->posY = ws.height / 2;

    this->speedX = this->default_speedX;
    this->speedY = this->default_speedY;
}

float Ball::getX() const { return this->posX; }
float Ball::getY() const { return this->posY; }

std::vector<std::vector<char>> Ball::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
