#pragma once
#include <cstddef>
#include <string>
#include "assets.hpp"
#include <vector>

class Screen {
  public:
    Screen();
    ~Screen();
    void draw();
    void addMatrix(Vector2D pos, const std::vector<std::vector<char>> &);
    void addText(Vector2D pos, std::string);
    void reset(char fill);
    void exit() const;
    Size2D getGameSize() const;

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;
    Screen(Screen &&other) noexcept;
    Screen &operator=(Screen &&other) noexcept;

  private:
    std::vector<std::vector<char>> ScreenVector;
    std::vector<std::vector<char>> ScreenVectorOld;
    struct Size2D ws;

    void drawBuff();
    static void showWin(Vector2D pos, Size2D size,
                        const std::string &text, const std::string &secondText);
    void addToBuff(Vector2D pos,
                   const std::vector<std::vector<char>> &vec, size_t y,
                   size_t x);

    static const size_t offsetTop;
    static const size_t offsetBottom;
    static const size_t offsetLeft;
    static const size_t offsetRight;
};
