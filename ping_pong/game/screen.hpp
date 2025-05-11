#pragma once
#include "assets.hpp"
#include <chrono>
#include <vector>

class screen {
  public:
    screen();
    ~screen();
    void draw(size_t frame_time = 0);
    void add(int posY, int posX, std::vector<std::vector<char>>);
    void reset(char fill);
    scrsize getGameSize() const;
    scrsize getScreenSize() const;

  private:
    std::vector<std::vector<char>> screen_vector;
    std::vector<std::vector<char>> screen_vector_old;
    struct scrsize ws;

    static const size_t offset_top;
    static const size_t offset_bottom;
    static const size_t offset_left;
    static const size_t offset_right;
};
