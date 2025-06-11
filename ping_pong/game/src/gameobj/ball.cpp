#include "gameobj/ball.hpp"
#include <vector>
#include "assets.hpp"

Ball::Ball(float speedX, float speedY, size_t width, size_t height)
    : size(width, height), defaultSpeed(speedX, speedY) {}
Ball::Ball(Vector2D speed, Size2D size)
    : size(size), defaultSpeed(speed) {}

void Ball::tick(size_t frameTimeMs) {
    this->pos += this->speed * frameTimeMs;
}

void Ball::reset(Size2D ws) {
    this->pos.x = static_cast<float>(ws.width) / 2;
    this->pos.y = static_cast<float>(ws.height) / 2;

    this->speed = this->defaultSpeed;
}

Vector2D Ball::getPos() const { return pos; }

void Ball::setX(float x) { this->pos.x = x; }
void Ball::setY(float y) { this->pos.y = y; }

void Ball::setPositiveX() {
    speed.x = (speed.x < 0) ? -speed.x : speed.x;
}
void Ball::setNegativeX() {
    speed.x = (speed.x > 0) ? -speed.x : speed.x;
}

void Ball::setPositiveY() {
    speed.y = (speed.y < 0) ? -speed.y : speed.y;
}
void Ball::setNegativeY() {
    speed.y = (speed.y > 0) ? -speed.y : speed.y;
}

Size2D Ball::getSize() const { return size; }

std::vector<std::vector<char>> Ball::getMatrix() const {
    std::vector<std::vector<char>> matrix(size.height,
                                          std::vector<char>(size.width, '#'));
    return matrix;
}
