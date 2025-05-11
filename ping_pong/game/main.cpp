#include <chrono>

#include "assets.hpp"
#include "gameobjects.hpp"
#include "screen.hpp"

int main(int argc, char const *argv[]) {

    screen sc;
    ball bl(0.05, 0.025, 6, 3);
    player lpl(3, 7, playermode::bot, playerpos::left);
    player rpl(3, 7, playermode::bot, playerpos::right);

    size_t frame_time = 0;
    while (true) {
        auto timer_start = std::chrono::high_resolution_clock::now();

        lpl.tick(sc.getGameSize(), bl);
        rpl.tick(sc.getGameSize(), bl);
        bl.tick(sc.getGameSize(), frame_time);

        sc.reset('-');
        sc.add(lpl.getPos(), lpl.calcX(sc.getGameSize()), lpl.getMatrix());
        sc.add(rpl.getPos(), rpl.calcX(sc.getGameSize()), rpl.getMatrix());
        sc.add(bl.getY(), bl.getX(), bl.getMatrix());
        sc.draw(frame_time);

        auto timer_end = std::chrono::high_resolution_clock::now();
        fps_lock(std::chrono::duration_cast<std::chrono::milliseconds>(
                     timer_end - timer_start),
                 90);
        auto timer_end_lock = std::chrono::high_resolution_clock::now();
        frame_time = std::chrono::duration_cast<std::chrono::milliseconds>(
                         timer_end_lock - timer_start)
                         .count();
    }
    return 0;
}
