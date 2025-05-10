#pragma once
#include "assets.hpp"
#include <vector>
#include <chrono>

class screen {
  public:
    screen();
    ~screen();
    void draw(bool showfps);
    void add(int posY, int posX, std::vector<std::vector<char>> vec);
    void reset(char fill);
    void getSize(scrsize& ws) const;

  private:
    std::vector<std::vector<char>> screen_vector;
    std::vector<std::vector<char>> screen_vector_old;
    struct scrsize ws;
    std::chrono::high_resolution_clock::time_point timer;
};
