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
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);

    if (has_colors())
        start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    curs_set(0);

    size_t height;
    size_t width;
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
        this->ws.height - Screen::offset_top - Screen::offset_bottom,
        this->ws.width - Screen::offset_left - Screen::offset_right};
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

void Screen::draw(size_t frameTimeMs) {
    drawBuff();
    printFps(frameTimeMs);
    refresh();
}

void Screen::drawBuff() {
    for (size_t y = 0; y < this->ws.height; y++) {
        for (size_t x = 0; x < this->ws.width; x++) {

            const char *screen_ch = &Screen_vector[y][x];
            char *screen_ch_old = &Screen_vector_old[y][x];

            if (*screen_ch != *screen_ch_old) {
                mvaddch(y, x, *screen_ch);
                *screen_ch_old = *screen_ch;
            }
        }
    }
}

void Screen::printFps(size_t frameTimeMs) {
    if (frameTimeMs > 0) {
        std::string fps = std::format("{}fps", 1000 / frameTimeMs);
        for (size_t i = 0; i < fps.length(); i++) {
            Screen_vector[0][i] = fps[i];
            Screen_vector_old[0][i] = fps[i];
        }
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", fps.c_str());
        attroff(COLOR_PAIR(1));
    }
}

void Screen::addToBuff(size_t posY, size_t posX,
                 const std::vector<std::vector<char>> &vec, size_t y, size_t x) {
    size_t cursorX = posX + x + Screen::offset_left;
    size_t cursorY = posY + y + Screen::offset_top;
    if (cursorY < Screen_vector.size() - Screen::offset_bottom &&
        cursorX < Screen_vector[0].size() - Screen::offset_right && vec[y][x] != 0) {
        Screen_vector[cursorY][cursorX] =
            vec[y][x];
    }
}

void Screen::add(int posY, int posX,
                 const std::vector<std::vector<char>> &vec) {
    if (vec.empty() || vec[0].empty())
        return;

    posY = (posY < 0) ? 0 : posY;
    posX = (posX < 0) ? 0 : posX;

    for (size_t y = 0; y < vec.size(); y++) {
        for (size_t x = 0; x < vec[0].size(); x++) {
            addToBuff(posY, posX, vec, y, x);
        }
    }
}

void Screen::exit() const {
    const std::string text = "Game over!";
    const std::string secondText = "Press any key to continue...";
    const size_t width = std::max(text.length(), secondText.length()) + 4;
    const size_t height = 6;

    showWin((this->ws.width - width) / 2, (this->ws.height - height) / 2, width, height, text, secondText);
}

void Screen::showWin(size_t posX, size_t posY, size_t width, size_t height, const std::string& text, const std::string& secondText) {
    WINDOW *popup = newwin(height, width, posY, posX);
    box(popup, 0, 0);

    mvwprintw(popup, 2, (width - text.length()) / 2, "%s", text.c_str());

    init_pair(3, COLOR_RED, COLOR_BLACK);
    wattron(popup, COLOR_PAIR(3));
    mvwprintw(popup, 3, (width - secondText.length()) / 2, "%s", secondText.c_str());
    wattroff(popup, COLOR_PAIR(3));

    wrefresh(popup);
    wgetch(popup);
    delwin(popup);
}
