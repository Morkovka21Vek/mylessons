#pragma once
#include "assets.hpp"
#include <cstddef>
#include <vector>

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

enum class playermode { bot };
enum class playerpos { left, right };

class player {
  public:
    player(int width, int height, enum playermode mode, enum playerpos posX);
    bool tick(struct scrsize ws, ball bl);
    int getScore() const;
    int getPos() const;
    size_t calcX(struct scrsize ws) const;
    void reset(struct scrsize ws);
    std::vector<std::vector<char>> getMatrix() const;

  private:
    int pos;
    int score;
    const size_t width;
    const size_t height;
    const enum playermode mode;
    const enum playerpos posX;

    int bot(float posY);
};
