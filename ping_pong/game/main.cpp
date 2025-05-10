#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <fcntl.h>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "assets.hpp"
#include "gameobjects.hpp"
#include "screen.hpp"

void fps_lock(size_t frame_time, size_t fpscount);

int main(int argc, char const *argv[]) {
    screen sc;

    struct scrsize ws;
    sc.getSize(ws);

    ball bl(0.05, 0.025, 3, 3);
    player lpl(3, 7, playermode::bot);
    player rpl(3, 7, playermode::bot);

    std::vector<std::vector<char>> img = {
        {'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};

    size_t frame_time = 0;

    while (true) {
        auto timer_start = std::chrono::high_resolution_clock::now();
        bl.tick(ws, frame_time);
        sc.reset('-');
        sc.add(bl.getY(), bl.getX(), img);
        sc.draw(true);

        auto timer_end = std::chrono::high_resolution_clock::now();
        fps_lock(std::chrono::duration_cast<std::chrono::milliseconds> (timer_end - timer_start).count(), 90);
        auto timer_end_lock = std::chrono::high_resolution_clock::now();
        frame_time = std::chrono::duration_cast<std::chrono::milliseconds> (timer_end_lock - timer_start).count();
    }
    return 0;
}

void fps_lock(size_t frame_time, size_t fpscount) {
    size_t timesleep = 1000/fpscount - frame_time;
    timesleep = (timesleep < 0) ? 0 : timesleep;
    std::this_thread::sleep_for(std::chrono::milliseconds(timesleep));
}
