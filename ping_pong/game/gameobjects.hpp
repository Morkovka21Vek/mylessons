#pragma once
#include "assets.hpp"
#include <cstddef>

class ball {
  public:
    ball(float _speedX, float _speedY, int _sizeX, int _sizeY);
    void tick(struct scrsize, size_t frame_time);
    void reset(struct scrsize);
    float getX() const;
    float getY() const;

  private:
    float posX;
    float posY;
    float speedX;
    float speedY;
    const int sizeX;
    const int sizeY;

    const float default_speedX;
    const float default_speedY;
};

enum class playermode { bot };

class player {
    public:
        player(int width, int height, enum playermode mode);
        bool tick(struct scrsize ws, ball bl);
        int getScore() const;
        void reset(struct scrsize ws);

    private:
        int pos;
        int score;
        const int width;
        const int height;
        const enum playermode mode;

        int bot(float posY);
};

