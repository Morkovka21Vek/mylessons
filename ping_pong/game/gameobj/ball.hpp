#pragma once
#include <vector>
#include <cstddef>
#include "assets.hpp"

class Ball {
  public:
    Ball(float _speedX, float _speedY, int _width, int _height);
    void tick(struct scrsize, size_t frame_time);
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

  private:
    float posX;
    float posY;
    float speedX;
    float speedY;
    const size_t width;
    const size_t height;

    const float default_speedX;
    const float default_speedY;
};
