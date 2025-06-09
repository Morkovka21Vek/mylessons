#pragma once
#include <cstddef>
#include <vector>

enum class Playermode { bot, keyboard };
enum class Playerpos { left, right };

class Player {
  public:
    Player(int width, int height, enum Playermode mode, enum Playerpos posX);
    void tick(struct scrsize ws, float ballPosY);

    int getPos() const;
    size_t calcX(struct scrsize ws) const;
    size_t getWidth() const;
    size_t getHeight() const;
    void reset(struct scrsize ws);
    Playerpos getPlayerposX() const;
    std::vector<std::vector<char>> getMatrix() const;

  private:
    int pos = -1;
    const size_t width;
    const size_t height;
    const enum Playermode mode;
    const enum Playerpos posX;

    int correctPos(int val, const scrsize ws) const;

    int bot(float posY) const;
    int keyboard() const;
};
