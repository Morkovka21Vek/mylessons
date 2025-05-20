#include <thread>
#include "game.hpp"

const size_t Game::MAX_FPS = 60;

Game::Game(): screen(), scboard(), ball(Ball(0.05, 0.025, 6, 3)), leftPl(Player(3, 7, Playermode::keyboard, Playerpos::left)), rightPl(Player(3, 7, Playermode::bot, Playerpos::right))
{}

void Game::loop() {
    size_t frame_time_ms = 0;

    do {
        auto time_start = std::chrono::high_resolution_clock::now();

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

        auto time_middle = std::chrono::high_resolution_clock::now();
        fps_lock(std::chrono::duration_cast<std::chrono::milliseconds>(
                     time_middle - time_start),
                 MAX_FPS);
        auto time_end = std::chrono::high_resolution_clock::now();
        frame_time_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                     time_end - time_start)
                     .count();

    } while(scboard.getScoreLeft() < 3 && scboard.getScoreRight() < 3);
    screen.exit();
}


void Game::fps_lock(std::chrono::milliseconds frame_time_ms, size_t fpscount) const {
    long timesleep = 1000 / fpscount - frame_time_ms.count();
    if (timesleep > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timesleep));
    }
}
