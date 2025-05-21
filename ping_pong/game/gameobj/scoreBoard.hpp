#pragma once
#include <vector>
#include "assets.hpp"

class ScoreBoard {
    public:
        ScoreBoard() = default;

        void addPointLeft();
        void setScoreLeft(int score);
        int getScoreLeft() const;

        void addPointRight();
        void setScoreRight(int score);
        int getScoreRight() const;

        std::vector<std::vector<char>> getMatrix() const;
        size_t calcX(struct scrsize ws) const;
    private:
        int lscore = 0;
        int rscore = 0;

        static const size_t width;

        void addSymbolToMatrix(std::vector<std::vector<char>>& matrix, const std::vector<std::vector<char>>& symbol, size_t posY, size_t posX) const;
        std::vector<std::vector<char>> getChar(char ch) const;
};
