#include "gameobj/scoreBoard.hpp"
#include <vector>
#include "assets.hpp"

const size_t ScoreBoard::width = 12;

ScoreBoard::ScoreBoard(): lscore(0), rscore(0)
{}

void ScoreBoard::addPointLeft() {
    this->lscore++;
}

void ScoreBoard::setScoreLeft(int score) {
    lscore = score;
}

int ScoreBoard::getScoreLeft() const {
    return this->lscore;
}

void ScoreBoard::addPointRight() {
    this->rscore++;
}

void ScoreBoard::setScoreRight(int score) {
    this->rscore = score;
}

int ScoreBoard::getScoreRight() const {
    return this->rscore;
}

size_t ScoreBoard::calcX(struct scrsize ws) const {
    return (ws.width - this->width) / 2;
}

std::vector<std::vector<char>> ScoreBoard::getMatrix() const {
    std::vector<std::vector<char>> matrix(6,
                                          std::vector<char>(this->width, '\0'));

    this->addSymbolToMatrix(matrix, this->getChar('0' + (this->lscore % 10)), 0, 0);
    this->addSymbolToMatrix(matrix, this->getChar('.'), 0, 5);
    this->addSymbolToMatrix(matrix, this->getChar('.'), 4, 5);
    this->addSymbolToMatrix(matrix, this->getChar('0' + (this->rscore % 10)), 0, 8);

    return matrix;
}

void ScoreBoard::addSymbolToMatrix(std::vector<std::vector<char>>& matrix, const std::vector<std::vector<char>>& symbol, int posY, int posX) const {
    for (size_t y = 0; y < symbol.size(); y++) {
        for (size_t x = 0; x < symbol[0].size(); x++) {
            if (posY + y >= matrix.size()    || posY + y < 0 ||
                posX + x >= matrix[0].size() || posX + x < 0) {
                continue;
            }
            matrix[posY+y][posX+x] = symbol[y][x];
        }
    }
}

std::vector<std::vector<char>> ScoreBoard::getChar(char ch) const {
    const std::vector<std::vector<char>> symbol_0 = {{'0', '0', '0', '0'}, {'0', '\0', '\0', '0'},
                                    {'0', '\0', '\0', '0'}, {'0', '\0', '\0', '0'},
                                    {'0', '\0', '\0', '0'}, {'0', '0', '0', '0'}};

    const std::vector<std::vector<char>> symbol_1 = {
        {'\0', '1', '1'}, {'\0', '1', '1'}, {'\0', '1', '1'},
        {'\0', '1', '1'}, {'\0', '1', '1'}, {'\0', '1', '1'}};

    const std::vector<std::vector<char>> symbol_2 = {{'2', '2', '2', '2'}, {'\0', '\0', '\0', '2'},
                                       {'2', '2', '2', '2'}, {'2', '\0', '\0', '\0'},
                                       {'2', '\0', '\0', '\0'}, {'2', '2', '2', '2'}};

    const std::vector<std::vector<char>> symbol_3 = {
        {'3', '3', '3', '3'}, {'\0', '\0', '\0', '3'}, {'3', '3', '3', '3'},
        {'\0', '\0', '\0', '3'}, {'\0', '\0', '\0', '3'}, {'3', '3', '3', '3'}};

    const std::vector<std::vector<char>> symbol_point = {{'#', '#'}, {'#', '#'}};

    const std::vector<std::vector<char>> symbol_err = {
        {'E', 'E', 'E', 'E'}, {'E', '\0', '\0', '\0'}, {'E', 'E', 'E', 'E'},
        {'E', '\0', '\0', '\0'}, {'E', '\0', '\0', '\0'}, {'E', 'E', 'E', 'E'}};

    switch (ch) {
        case '0': return symbol_0;
        case '1': return symbol_1;
        case '2': return symbol_2;
        case '3': return symbol_3;
        case '.': return symbol_point;
        default:  return symbol_err;
    }
    return symbol_err;
}
