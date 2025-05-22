#include "gameobj/ball.hpp"
#include "assets.hpp"
#include <vector>

Ball::Ball(float _speedX, float _speedY, int _width, int _height)
    : width(_width), height(_height), defaultSpeedX(_speedX),
      defaultSpeedY(_speedY) {}
void Ball::tick(struct scrsize ws, size_t frameTimeMs) {
    if (this->posX == -1 || this->posY == -1) {
        this->reset(ws);
    }

    this->posX += this->speedX * frameTimeMs;
    this->posY += this->speedY * frameTimeMs;
}

void Ball::reset(struct scrsize ws) {
    this->posX = ws.width / 2;
    this->posY = ws.height / 2;

    this->speedX = this->defaultSpeedX;
    this->speedY = this->defaultSpeedY;
}

float Ball::getX() const { return this->posX; }
float Ball::getY() const { return this->posY; }

void Ball::reverseX() { this->speedX = -this->speedX; }
void Ball::reverseY() { this->speedY = -this->speedY; }
void Ball::setX(float x) { this->posX = x; }
void Ball::setY(float y) { this->posY = y; }

void Ball::setPositiveX() {
    this->speedX = (this->speedX < 0) ? -this->speedX : this->speedX;
}

void Ball::setNegativeX() {
    this->speedX = (this->speedX > 0) ? -this->speedX : this->speedX;
}

size_t Ball::getWidth() const { return this->width; }
size_t Ball::getHeight() const { return this->height; }

std::vector<std::vector<char>> Ball::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
