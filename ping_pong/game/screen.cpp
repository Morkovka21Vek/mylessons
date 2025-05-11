#include "screen.hpp"
#include "assets.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

const size_t screen::offset_top = 1;
const size_t screen::offset_bottom = 1;
const size_t screen::offset_left = 0;
const size_t screen::offset_right = 0;

screen::screen() {
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

    this->screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, 0));
    this->screen_vector_old.assign(this->ws.height,
                                   std::vector<char>(this->ws.width, 0));
}

screen::~screen() { endwin(); }

scrsize screen::getScreenSize() const {
    return this->ws;
}

scrsize screen::getGameSize() const {
    struct scrsize crop_ws = {
        this->ws.height - this->offset_top - this->offset_bottom,
        this->ws.width - this->offset_left - this->offset_right};
    return crop_ws;
}

void screen::reset(char fill) {
    this->screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, fill));

    for (size_t i = 0; i < this->ws.width; i++) {
        screen_vector[0][i] = '#';
        screen_vector[ws.height - 1][i] = '#';
    }
}

void screen::draw(size_t frame_time) {
    for (size_t y = 0; y < this->ws.height; y++) {
        for (size_t x = 0; x < this->ws.width; x++) {
            if (screen_vector[y][x] == screen_vector_old[y][x]) {
                continue;
            }
            //if (screen_vector[y][x] == '#') {
            //    attron(COLOR_PAIR(2));
            //    mvaddch(y, x, screen_vector[y][x]);
            //    attroff(COLOR_PAIR(2));
            //} else {
            mvaddch(y, x, screen_vector[y][x]);
            //}
            screen_vector_old[y][x] = screen_vector[y][x];
        }
    }

    if (frame_time > 0) {
        std::string fps =
            std::to_string((frame_time == 0) ? 0 : 1000 / frame_time) + "fps";
        for (size_t i = 0; i < fps.length(); i++) {
            screen_vector[0][i] = fps[i];
            screen_vector_old[0][i] = fps[i];
        }
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", fps.c_str());
        attroff(COLOR_PAIR(1));
    }

    refresh();
}

void screen::add(int posY, int posX, std::vector<std::vector<char>> vec) {
    if (vec.empty() || vec[0].empty())
        return;

    for (size_t y = 0; y < vec.size(); y++) {
        for (size_t x = 0; x < vec[0].size(); x++) {
            if (posY + y + this->offset_top  >= screen_vector.size()    - this->offset_bottom ||
                posX + x + this->offset_left >= screen_vector[0].size() - this->offset_right) {
                continue;
            }
            screen_vector[offset_top + posY + y][offset_left + posX + x] = vec[y][x];
        }
    }
}

/*
void drawText(const std::string text, const int spaceSize,
              const int ws.width, const int ws.height,
              const char background_char) {
    int widthText = 0;

    for (char ch : text) {
        int width = 0, height = 0;
        getSizeCh(ch, width, height);
        widthText += width + spaceSize;
    }

    for (int y = 0; y < ws.height; y++) {
        std::cout << "\033[" << y + 1 << ";1H";

        for (int x = 0; x < ws.width; x++) {
            int drawPosX = static_cast<int>(ws.width / 2 - widthText / 2);
            char drawCh = background_char;

            for (char ch : text) {
                int width = 0, height = 0;
                getSizeCh(ch, width, height);

                char tempCh;
                if ((tempCh = getChar(
                         ch, drawPosX,
                         static_cast<int>(ws.height / 2 - height / 2), x,
                         y)) != ' ') {
                    drawCh = tempCh;
                    break;
                }
                drawPosX += width + spaceSize;
            }
            std::cout << drawCh;
        }
    }
    std::cout << std::endl;
}

char getChar(char ch, int posX, int posY, int x, int y) {
    int width = 0, height = 0;
    getSizeCh(ch, width, height);

    if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
        return getSymbolCh(ch, x - posX, y - posY);
    }
    return ' ';
}

inline bool pathFind(const prediction &pred, int x, int y) {
    for (int i = 0; i < static_cast<int>(pred.pathX.size()); i++) {
        if (pred.pathX[i] == x && pred.pathY[i] == y)
            return 1;
    }
    return 0;
}
*/
