#pragma once
#include "assets.hpp"
#include <chrono>
#include <vector>

class Screen {
  public:
    Screen();
    ~Screen();
    void draw(size_t frameTimeMs = 0);
    void add(int posY, int posX, const std::vector<std::vector<char>> &);
    void reset(char fill);
    void exit() const;
    scrsize getGameSize() const;

    Screen(const Screen&) = delete;
    Screen& operator=(const Screen&) = delete;
    Screen(Screen&&) noexcept = default;
    Screen& operator=(Screen&&) noexcept = default;

  private:
    std::vector<std::vector<char>> Screen_vector;
    std::vector<std::vector<char>> Screen_vector_old;
    struct scrsize ws;

    void drawBuff();
    void printFps(size_t frameTimeMs);
    static void showWin(size_t posX, size_t posY, size_t width, size_t height, const std::string& text, const std::string& secondText);
    void addToBuff(size_t posY, size_t posX,
                 const std::vector<std::vector<char>> &vec, size_t y, size_t x);

    static const size_t offset_top;
    static const size_t offset_bottom;
    static const size_t offset_left;
    static const size_t offset_right;
};
