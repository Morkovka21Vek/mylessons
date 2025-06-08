#include "gameobj/scoreBoard.hpp"
#include <unordered_map>
#include <vector>
#include <screen.hpp>

const size_t ScoreBoard::width = 12;

void ScoreBoard::addPointLeft() { this->lscore++; }

void ScoreBoard::setScoreLeft(int score) { lscore = score; }

int ScoreBoard::getScoreLeft() const { return this->lscore; }

void ScoreBoard::addPointRight() { this->rscore++; }

void ScoreBoard::setScoreRight(int score) { this->rscore = score; }

int ScoreBoard::getScoreRight() const { return this->rscore; }

size_t ScoreBoard::calcX(struct scrsize ws) const {
    return (ws.width - ScoreBoard::width) / 2;
}

std::vector<std::vector<char>> ScoreBoard::getMatrix() const {
    std::vector<std::vector<char>> matrix(
        6, std::vector<char>(ScoreBoard::width, '\0'));

    this->addSymbolToMatrix(matrix, this->getChar('0' + (this->lscore % 10)), 0,
                            0);
    this->addSymbolToMatrix(matrix, this->getChar('.'), 0, 5);
    this->addSymbolToMatrix(matrix, this->getChar('.'), 4, 5);
    this->addSymbolToMatrix(matrix, this->getChar('0' + (this->rscore % 10)), 0,
                            8);

    return matrix;
}

void ScoreBoard::addSymbolToMatrix(std::vector<std::vector<char>> &matrix,
                                   const std::vector<std::vector<char>> &symbol,
                                   size_t posY, size_t posX) const {
    for (size_t y = 0; y < symbol.size(); y++) {
        for (size_t x = 0; x < symbol[0].size(); x++) {
            if (posY + y >= matrix.size() || posX + x >= matrix[0].size()) {
                continue;
            }
            matrix[posY + y][posX + x] = symbol[y][x];
        }
    }
}

std::vector<std::vector<char>> ScoreBoard::getChar(char ch) const {
    static const std::unordered_map<char, std::vector<std::vector<char>>>
        symbols = {{'0',
                    {{'0', '0', '0', '0'},
                     {'0', '\0', '\0', '0'},
                     {'0', '\0', '\0', '0'},
                     {'0', '\0', '\0', '0'},
                     {'0', '\0', '\0', '0'},
                     {'0', '0', '0', '0'}}},
                   {'1',
                    {{'\0', '1', '1'},
                     {'\0', '1', '1'},
                     {'\0', '1', '1'},
                     {'\0', '1', '1'},
                     {'\0', '1', '1'},
                     {'\0', '1', '1'}}},
                   {'2',
                    {{'2', '2', '2', '2'},
                     {'\0', '\0', '\0', '2'},
                     {'2', '2', '2', '2'},
                     {'2', '\0', '\0', '\0'},
                     {'2', '\0', '\0', '\0'},
                     {'2', '2', '2', '2'}}},
                   {'3',
                    {{'3', '3', '3', '3'},
                     {'\0', '\0', '\0', '3'},
                     {'3', '3', '3', '3'},
                     {'\0', '\0', '\0', '3'},
                     {'\0', '\0', '\0', '3'},
                     {'3', '3', '3', '3'}}},
                   {'.', {{'#', '#'}, {'#', '#'}}},
                   {'E',
                    {{'E', 'E', 'E', 'E'},
                     {'E', '\0', '\0', '\0'},
                     {'E', 'E', 'E', 'E'},
                     {'E', '\0', '\0', '\0'},
                     {'E', '\0', '\0', '\0'},
                     {'E', 'E', 'E', 'E'}}}};

    auto it = symbols.find(ch);
    return (it != symbols.end()) ? it->second : symbols.at('E');
}
