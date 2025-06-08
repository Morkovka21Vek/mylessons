#pragma once
#include <string>
#include <vector>
#include <cstddef>

struct scrsize {
    size_t height;
    size_t width;
};

class Screen {
  public:
    Screen();
    ~Screen();
    void draw(size_t frameTimeMs = 0);
    void add(int posY, int posX, const std::vector<std::vector<char>> &);
    void reset(char fill);
    void exit() const;
    scrsize getGameSize() const;

    Screen(const Screen &) = delete;
    Screen &operator=(const Screen &) = delete;
    Screen(Screen &&other) noexcept;
    Screen &operator=(Screen &&other) noexcept;

  private:
    std::vector<std::vector<char>> ScreenVector;
    std::vector<std::vector<char>> ScreenVectorOld;
    struct scrsize ws;

    void drawBuff();
    void printFps(size_t frameTimeMs);
    static void showWin(size_t posX, size_t posY, size_t width, size_t height,
                        const std::string &text, const std::string &secondText);
    void addToBuff(size_t posY, size_t posX,
                   const std::vector<std::vector<char>> &vec, size_t y,
                   size_t x);

    static const size_t offsetTop;
    static const size_t offsetBottom;
    static const size_t offsetLeft;
    static const size_t offsetRight;
};
