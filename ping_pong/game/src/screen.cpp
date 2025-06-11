#include "screen.hpp"
#include <ncurses.h>
#include <string>
#include <vector>
#include <string>
#include "assets.hpp"

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

Screen::Screen(Screen &&other) noexcept
    : ScreenVector(std::move(other.ScreenVector)),
      ScreenVectorOld(std::move(other.ScreenVectorOld)),
      ws(std::move(other.ws)) {}

Screen &Screen::operator=(Screen &&other) noexcept {
    if (this != &other) {
        ScreenVector = std::move(other.ScreenVector);
        ScreenVectorOld = std::move(other.ScreenVectorOld);
        ws = std::move(other.ws);
    }
    return *this;
}

Size2D Screen::getGameSize() const {
    return Size2D(
        ws.height - Screen::offsetTop - Screen::offsetBottom,
        ws.width - Screen::offsetLeft - Screen::offsetRight);
}

void Screen::reset(char fill) {
    this->ScreenVector.assign(this->ws.height,
                              std::vector<char>(this->ws.width, fill));

    for (size_t i = 0; i < this->ws.width; i++) {
        ScreenVector[0][i] = '#';
        ScreenVector[ws.height - 1][i] = '#';
    }
}

void Screen::draw() {
    drawBuff();
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

void Screen::addText(Vector2D pos, std::string text) {
    for (size_t i = 0; i < text.length(); i++) {
        if (pos.x + i >= this->ws.width)
            break;
        ScreenVector[pos.y][pos.y + i] = text[i];
        ScreenVectorOld[pos.y][pos.y + i] = text[i];
    }
    attron(COLOR_PAIR(1));
    mvprintw(0, 0, "%s", text.c_str());
    attroff(COLOR_PAIR(1));
}

void Screen::addToBuff(Vector2D pos,
                       const std::vector<std::vector<char>> &vec, size_t y,
                       size_t x) {
    size_t cursorX = pos.x + x + Screen::offsetLeft;
    size_t cursorY = pos.y + y + Screen::offsetTop;
    if (cursorY < ScreenVector.size() - Screen::offsetBottom &&
        cursorX < ScreenVector[0].size() - Screen::offsetRight &&
        vec[y][x] != 0) {
        ScreenVector[cursorY][cursorX] = vec[y][x];
    }
}

void Screen::addMatrix(Vector2D pos,
                 const std::vector<std::vector<char>> &vec) {
    if (vec.empty() || vec[0].empty())
        return;

    pos.y = (pos.y < 0) ? 0 : pos.y;
    pos.x = (pos.x < 0) ? 0 : pos.x;

    for (size_t y = 0; y < vec.size(); y++) {
        for (size_t x = 0; x < vec[0].size(); x++) {
            addToBuff(pos, vec, y, x);
        }
    }
}

void Screen::exit() const {
    const std::string text = "Game over!";
    const std::string secondText = "Press any key to continue...";
    const size_t width = std::max(text.length(), secondText.length()) + 4;
    const size_t height = 6;

    showWin(Vector2D(static_cast<float>(ws.width - width) / 2, static_cast<float>(ws.height - height) / 2), Size2D(width, height), text, secondText);
}

void Screen::showWin(Vector2D pos, Size2D size,
                     const std::string &text, const std::string &secondText) {
    WINDOW *popup = newwin(size.height, size.width, pos.y, pos.x);
    box(popup, 0, 0);

    mvwprintw(popup, 2, (size.width - text.length()) / 2, "%s", text.c_str());

    init_pair(3, COLOR_RED, COLOR_BLACK);
    wattron(popup, COLOR_PAIR(3));
    mvwprintw(popup, 3, (size.width - secondText.length()) / 2, "%s",
              secondText.c_str());
    wattroff(popup, COLOR_PAIR(3));

    wrefresh(popup);
    wgetch(popup);
    delwin(popup);
}
