#pragma once
#include <vector>
#include <cstddef>
#include "assets.hpp"

class ball {
  public:
    ball(float _speedX, float _speedY, int _width, int _height);
    void tick(struct scrsize, size_t frame_time);
    void reset(struct scrsize);
    float getX() const;
    float getY() const;
    std::vector<std::vector<char>> getMatrix() const;

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
