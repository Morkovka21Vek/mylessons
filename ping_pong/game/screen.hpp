#pragma once
#include "assets.hpp"
#include <chrono>
#include <vector>

class Screen {
  public:
    Screen();
    ~Screen();
    void draw(size_t frame_time = 0);
    void add(int posY, int posX, const std::vector<std::vector<char>> &);
    void reset(char fill);
    void exit() const;
    scrsize getGameSize() const;

  private:
    std::vector<std::vector<char>> Screen_vector;
    std::vector<std::vector<char>> Screen_vector_old;
    struct scrsize ws;

    static const size_t offset_top;
    static const size_t offset_bottom;
    static const size_t offset_left;
    static const size_t offset_right;
};
