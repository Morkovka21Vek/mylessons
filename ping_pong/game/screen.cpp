#include "screen.hpp"
#include "assets.hpp"
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <chrono>

screen::screen() {
    initscr();
    nocbreak();
    echo();

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_WHITE, COLOR_WHITE);
    }
    curs_set(0);

    int height, width;
    getmaxyx(stdscr, height, width);
    this->ws = {height, width};

    this->screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, 0));
    this->screen_vector_old.assign(this->ws.height,
                                   std::vector<char>(this->ws.width, 0));
}

screen::~screen() { endwin(); }

void screen::getSize(scrsize& ws) const{
    ws = this->ws;
}

void screen::reset(char fill) {
    this->screen_vector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, fill));

    for (int i = 0; i < this->ws.width; i++) {
        screen_vector[0][i] = '#';
        screen_vector[ws.height-1][i] = '#';
    }
}

void screen::draw(bool showfps) {
    for (int y = 0; y < this->ws.height; y++) {
        for (int x = 0; x < this->ws.width; x++) {
            if (screen_vector[y][x] == screen_vector_old[y][x]) {
                continue;
            }
            if (screen_vector[y][x] == '#') {
                attron(COLOR_PAIR(2));
                mvaddch(y, x, screen_vector[y][x]);
                attroff(COLOR_PAIR(2));
            } else {
                mvaddch(y, x, screen_vector[y][x]);
            }
            screen_vector_old[y][x] = screen_vector[y][x];
        }
    }
    refresh();

    auto timer_now = std::chrono::high_resolution_clock::now();
    size_t frame_time = std::chrono::duration_cast<std::chrono::milliseconds> (timer_now - this->timer).count();

    size_t fpscount = (frame_time == 0) ? 0 : 1000/frame_time;
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "%ldfps", fpscount);
    attroff(COLOR_PAIR(1));

    this->timer = std::chrono::high_resolution_clock::now();
}

void screen::add(int posY, int posX, std::vector<std::vector<char>> vec) {
    if (vec.size() < 1)
        return;

    for (size_t y = 0; y < vec.size(); y++) {
        for (size_t x = 0; x < vec[0].size(); x++) {
            if (posY + y >= screen_vector.size() || posY + y < 0 ||
                posX + x >= screen_vector[0].size() || posX + x < 0) {
                continue;
            }
            screen_vector[posY + y][posX + x] = vec[y][x];
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
