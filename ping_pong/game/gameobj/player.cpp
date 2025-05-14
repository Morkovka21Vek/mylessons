#include "assets.hpp"
#include "gameobj/player.hpp"
#include <vector>

player::player(int _width, int _height, enum playermode _mode, enum playerpos _posX)
    : pos(-1), score(0), width(_width), height(_height), mode(_mode), posX(_posX) {}

void player::tick(struct scrsize ws) {
    using enum playermode;

    if (this->pos == -1) {
        this->reset(ws);
    }

    int temppos = 0;
    switch (this->mode) {
    case bot:
        temppos = this->bot(0);//bl.getY());
    }
    temppos = (temppos < 0) ? 0 : temppos;
    this->pos = (temppos + this->height > ws.height)
                    ? ws.height - this->height
                    : temppos;
}

int player::getScore() const { return this->score; }

int player::getPos() const { return this->pos; }

size_t player::calcX(struct scrsize ws) const {
    return (this->posX == playerpos::left) ? 0 : ws.width - this->width;
}

void player::reset(struct scrsize ws) {
    this->pos = (ws.height - this->height) / 2;
}

std::vector<std::vector<char>> player::getMatrix() const {
    std::vector<std::vector<char>> matrix(this->height,
                                          std::vector<char>(this->width, '#'));
    return matrix;
}
