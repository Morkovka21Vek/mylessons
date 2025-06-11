#pragma once
#include <cstddef>
#include <vector>
#include "assets.hpp"

enum class Playermode { bot, keyboard };
enum class PlayerSide { left, right };

class Player {
  public:
    Player(size_t width, size_t height, enum Playermode mode, enum PlayerSide side);
    Player(Size2D size, enum Playermode mode, enum PlayerSide side);
    void tick(Size2D ws, float ballPosY);

    int getPos() const;
    int calcX(Size2D ws) const;
    Size2D getSize() const;
    void reset(Size2D ws);
    PlayerSide getSide() const;
    std::vector<std::vector<char>> getMatrix() const;

  private:
    int pos = -1;
    const Size2D size;
    const enum Playermode mode;
    const enum PlayerSide side;

    int correctPos(int val, Size2D ws) const;

    int bot(float posY) const;
    int keyboard() const;
};
