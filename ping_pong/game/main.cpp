#include <chrono>

#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/scoreBoard.hpp"
#include "gameobj/collision.hpp"
#include "screen.hpp"

int main(int argc, char const *argv[]) {

    const size_t MAX_FPS = 60;

    Screen screen;
    ScoreBoard scboard;
    Ball ball(0.05, 0.025, 6, 3);
    Player leftPl(3, 7, Playermode::keyboard, Playerpos::left);
    Player rightPl(3, 7, Playermode::bot, Playerpos::right);

    size_t frame_time_ms = 0;
    while (true) {
        timer_start();

        leftPl.tick(screen.getGameSize(), ball.getY());
        rightPl.tick(screen.getGameSize(), ball.getY());
        ball.tick(screen.getGameSize(), frame_time_ms);

        CollisionSystem::handleAllCollisions(ball, leftPl, rightPl,
                                   screen.getGameSize(), scboard);

        screen.reset('-');
        screen.add(0, scboard.calcX(screen.getGameSize()), scboard.getMatrix());
        screen.add(leftPl.getPos(), leftPl.calcX(screen.getGameSize()), leftPl.getMatrix());
        screen.add(rightPl.getPos(), rightPl.calcX(screen.getGameSize()), rightPl.getMatrix());
        screen.add(ball.getY(), ball.getX(), ball.getMatrix());
        screen.draw(frame_time_ms);

        if (scboard.getScoreLeft() >= 3 || scboard.getScoreRight() >= 3) {
            screen.exit();
            break;
        }

        frame_time_ms = timer_end(MAX_FPS);
    }

    return 0;
}
