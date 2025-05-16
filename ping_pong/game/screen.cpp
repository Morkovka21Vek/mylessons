#include "screen.hpp"
#include "assets.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

const size_t Screen::offset_top = 1;
const size_t Screen::offset_bottom = 1;
const size_t Screen::offset_left = 0;
const size_t Screen::offset_right = 0;

Screen::Screen() {
    initscr();
    nocbreak();
    echo();

    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_WHITE);
    }
    curs_set(0);

    size_t height, width;
    getmaxyx(stdscr, height, width);
    this->ws = {height, width};

    this->Screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, 0));
    this->Screen_vector_old.assign(this->ws.height,
                                   std::vector<char>(this->ws.width, 0));
}

Screen::~Screen() { endwin(); }

scrsize Screen::getGameSize() const {
    struct scrsize crop_ws = {
        this->ws.height - this->offset_top - this->offset_bottom,
        this->ws.width - this->offset_left - this->offset_right};
    return crop_ws;
}

void Screen::reset(char fill) {
    this->Screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, fill));

    for (size_t i = 0; i < this->ws.width; i++) {
        Screen_vector[0][i] = '#';
        Screen_vector[ws.height - 1][i] = '#';
    }
}

void Screen::draw(size_t frame_time) {
    for (size_t y = 0; y < this->ws.height; y++) {
        for (size_t x = 0; x < this->ws.width; x++) {
            if (Screen_vector[y][x] == Screen_vector_old[y][x]) {
                continue;
            }
            // if (Screen_vector[y][x] == '#') {
            //     attron(COLOR_PAIR(2));
            //     mvaddch(y, x, Screen_vector[y][x]);
            //     attroff(COLOR_PAIR(2));
            // } else {
            mvaddch(y, x, Screen_vector[y][x]);
            //}
            Screen_vector_old[y][x] = Screen_vector[y][x];
        }
    }

    if (frame_time > 0) {
        std::string fps = std::to_string(1000 / frame_time) + "fps";
        for (size_t i = 0; i < fps.length(); i++) {
            Screen_vector[0][i] = fps[i];
            Screen_vector_old[0][i] = fps[i];
        }
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", fps.c_str());
        attroff(COLOR_PAIR(1));
    }

    refresh();
}

void Screen::add(int posY, int posX,
                 const std::vector<std::vector<char>> &vec) {
    if (vec.empty() || vec[0].empty())
        return;

    for (size_t y = 0; y < vec.size(); y++) {
        for (size_t x = 0; x < vec[0].size(); x++) {
            if (posY + y + this->offset_top >=
                    Screen_vector.size() - this->offset_bottom || posY + y < 0 ||
                posX + x + this->offset_left >=
                    Screen_vector[0].size() - this->offset_right || posY + y < 0) {
                continue;
            }
            if (vec[y][x] == 0) {
                continue;
            }

            Screen_vector[offset_top + posY + y][offset_left + posX + x] =
                vec[y][x];
        }
    }
}

/*
inline bool pathFind(const prediction &pred, int x, int y) {
    for (int i = 0; i < static_cast<int>(pred.pathX.size()); i++) {
        if (pred.pathX[i] == x && pred.pathY[i] == y)
            return 1;
    }
    return 0;
}
*/
