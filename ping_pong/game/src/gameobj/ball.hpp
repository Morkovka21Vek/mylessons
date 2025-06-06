#pragma once
#include "assets.hpp"
#include <cstddef>
#include <vector>

class Ball {
  public:
    Ball(float _speedX, float _speedY, int _width, int _height);
    void tick(struct scrsize, size_t frameTimeMs);
    void reset(struct scrsize);
    float getX() const;
    float getY() const;
    size_t getWidth() const;
    size_t getHeight() const;
    std::vector<std::vector<char>> getMatrix() const;

    void reverseX();
    void reverseY();
    void setX(float x);
    void setY(float y);

    void setPositiveX();
    void setNegativeX();

  private:
    float posX = -1;
    float posY = -1;
    float speedX;
    float speedY;
    const size_t width;
    const size_t height;

    const float defaultSpeedX;
    const float defaultSpeedY;
};
