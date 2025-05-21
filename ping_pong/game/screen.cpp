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

void Screen::draw(size_t frameTime) {
    drawBuff();
    printFps(frameTime);
    refresh();
}

void Screen::drawBuff() {
    for (size_t y = 0; y < this->ws.height; y++) {
        for (size_t x = 0; x < this->ws.width; x++) {

            char *screen_ch = &Screen_vector[y][x];
            char *screen_ch_old = &Screen_vector_old[y][x];

            if (*screen_ch != *screen_ch_old) {
                mvaddch(y, x, *screen_ch);
                *screen_ch_old = *screen_ch;
            }
        }
    }
}

void Screen::printFps(size_t frameTime) {
    if (frameTime > 0) {
        std::string fps = std::to_string(1000 / frameTime) + "fps";
        for (size_t i = 0; i < fps.length(); i++) {
            Screen_vector[0][i] = fps[i];
            Screen_vector_old[0][i] = fps[i];
        }
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", fps.c_str());
        attroff(COLOR_PAIR(1));
    }
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
                    Screen_vector[0].size() - this->offset_right || posY + y < 0 || vec[y][x] == 0) {
                continue;
            }
            Screen_vector[offset_top + posY + y][offset_left + posX + x] =
                vec[y][x];
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

void Screen::showWin(size_t posX, size_t posY, size_t width, size_t height, const std::string& text, const std::string& secondText) const {
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
