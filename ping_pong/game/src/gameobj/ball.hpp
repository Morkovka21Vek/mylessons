#pragma once
#include <cstddef>
#include <vector>
#include "assets.hpp"

class Ball {
  public:
    Ball(float speedX, float speedY, size_t width, size_t height);
    Ball(Vector2D speed, Size2D size);

    void tick(size_t frameTimeMs);
    void reset(Size2D ws);
    Vector2D getPos() const;
    Size2D getSize() const;
    std::vector<std::vector<char>> getMatrix() const;

    void setX(float x);
    void setY(float y);

    void setPositiveX();
    void setNegativeX();

    void setPositiveY();
    void setNegativeY();

  private:
    Vector2D pos;
    Vector2D speed;
    const Size2D size;

    const Vector2D defaultSpeed;
};
