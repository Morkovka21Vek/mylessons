#pragma once
#include "assets.hpp"
#include <cstddef>
#include <vector>

enum class playermode { bot };
enum class playerpos { left, right };

class player {
  public:
    player(int width, int height, enum playermode mode, enum playerpos posX);
    void tick(struct scrsize ws);
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

    int bot(float posY) const;
};
