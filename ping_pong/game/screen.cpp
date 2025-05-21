#include "screen.hpp"
#include "assets.hpp"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <ncurses.h>
#include <string>
#include <vector>

const size_t Screen::offsetTop = 1;
const size_t Screen::offsetBottom = 1;
const size_t Screen::offsetLeft = 0;
const size_t Screen::offsetRight = 0;

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

    this->ScreenVector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, 0));
    this->ScreenVectorOld.assign(this->ws.height,
                                   std::vector<char>(this->ws.width, 0));
}

Screen::~Screen() { endwin(); }

Screen::Screen(Screen&& other) noexcept
    : ScreenVector(std::move(other.ScreenVector)),
      ScreenVectorOld(std::move(other.ScreenVectorOld)),
      ws(std::move(other.ws)) {}

Screen& Screen::operator=(Screen&& other) noexcept {
    if (this != &other) {
        ScreenVector = std::move(other.ScreenVector);
        ScreenVectorOld = std::move(other.ScreenVectorOld);
        ws = std::move(other.ws);
    }
    return *this;
}

scrsize Screen::getGameSize() const {
    struct scrsize gameSize = {
        this->ws.height - Screen::offsetTop - Screen::offsetBottom,
        this->ws.width - Screen::offsetLeft - Screen::offsetRight};
    return gameSize;
}

void Screen::reset(char fill) {
    this->ScreenVector.assign(this->ws.height,
                               std::vector<char>(this->ws.width, fill));

    for (size_t i = 0; i < this->ws.width; i++) {
        ScreenVector[0][i] = '#';
        ScreenVector[ws.height - 1][i] = '#';
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

            const char *screenCh = &ScreenVector[y][x];
            char *screenChOld = &ScreenVectorOld[y][x];

            if (*screenCh != *screenChOld) {
                mvaddch(y, x, *screenCh);
                *screenChOld = *screenCh;
            }
        }
    }
}

void Screen::printFps(size_t frameTimeMs) {
    if (frameTimeMs > 0) {
        std::string fps = std::format("{}fps", 1000 / frameTimeMs);
        for (size_t i = 0; i < fps.length(); i++) {
            ScreenVector[0][i] = fps[i];
            ScreenVectorOld[0][i] = fps[i];
        }
        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "%s", fps.c_str());
        attroff(COLOR_PAIR(1));
    }
}

void Screen::addToBuff(size_t posY, size_t posX,
                 const std::vector<std::vector<char>> &vec, size_t y, size_t x) {
    size_t cursorX = posX + x + Screen::offsetLeft;
    size_t cursorY = posY + y + Screen::offsetTop;
    if (cursorY < ScreenVector.size() - Screen::offsetBottom &&
        cursorX < ScreenVector[0].size() - Screen::offsetRight && vec[y][x] != 0) {
        ScreenVector[cursorY][cursorX] =
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
