#include <chrono>
#include <thread>
#include "assets.hpp"

void fps_lock(std::chrono::milliseconds frame_time, size_t fpscount) {
    size_t timesleep = 1000 / fpscount - frame_time.count();
    timesleep = (timesleep < 0) ? 0 : timesleep;
    std::this_thread::sleep_for(std::chrono::milliseconds(timesleep));
}

#define char_size(ch, xsize, ysize)                                            \
    xsize = sizeof(ch[0]) / sizeof(char);                                      \
    ysize = sizeof(ch) / sizeof(ch[0]);

static const char zeroChar[6][4] = {{'0', '0', '0', '0'}, {'0', ' ', ' ', '0'},
                                    {'0', ' ', ' ', '0'}, {'0', ' ', ' ', '0'},
                                    {'0', ' ', ' ', '0'}, {'0', '0', '0', '0'}};

static const char oneChar[6][2] = {{'1', '1'}, {'1', '1'}, {'1', '1'},
                                   {'1', '1'}, {'1', '1'}, {'1', '1'}};

static const char twoChar[6][4] = {{'2', '2', '2', '2'}, {' ', ' ', ' ', '2'},
                                   {'2', '2', '2', '2'}, {'2', ' ', ' ', ' '},
                                   {'2', ' ', ' ', ' '}, {'2', '2', '2', '2'}};

static const char threeChar[6][4] = {
    {'3', '3', '3', '3'}, {' ', ' ', ' ', '3'}, {'3', '3', '3', '3'},
    {' ', ' ', ' ', '3'}, {' ', ' ', ' ', '3'}, {'3', '3', '3', '3'}};

static const char colonChar[6][2] = {{'#', '#'}, {'#', '#'}, {' ', ' '},
                                     {' ', ' '}, {'#', '#'}, {'#', '#'}};

static const char ballChar[5][9] = {
    {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
    {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
    {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
};
