#include "game.hpp"
#include <thread>

const size_t Game::MAXFPS = 60;

void Game::loop() {
    size_t frameTimeMs = 0;

    do {
        auto timeStart = std::chrono::high_resolution_clock::now();

        leftPl.tick(screen.getGameSize(), ball.getY());
        rightPl.tick(screen.getGameSize(), ball.getY());
        ball.tick(screen.getGameSize(), frameTimeMs);

        CollisionSystem::handleAllCollisions(ball, leftPl, rightPl,
                                             screen.getGameSize(), scboard);

        screen.reset('-');
        screen.add(0, scboard.calcX(screen.getGameSize()), scboard.getMatrix());
        screen.add(leftPl.getPos(), leftPl.calcX(screen.getGameSize()),
                   leftPl.getMatrix());
        screen.add(rightPl.getPos(), rightPl.calcX(screen.getGameSize()),
                   rightPl.getMatrix());
        screen.add(ball.getY(), ball.getX(), ball.getMatrix());
        screen.draw(frameTimeMs);

        auto timeMiddle = std::chrono::high_resolution_clock::now();
        fpsLock(std::chrono::duration_cast<std::chrono::milliseconds>(
                    timeMiddle - timeStart),
                MAXFPS);
        auto timeEnd = std::chrono::high_resolution_clock::now();
        frameTimeMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                          timeEnd - timeStart)
                          .count();

    } while (scboard.getScoreLeft() < 3 && scboard.getScoreRight() < 3);
    screen.exit();
}

void Game::fpsLock(std::chrono::milliseconds frameTimeMs, size_t fpscount) {
    long timesleep = 1000 / fpscount - frameTimeMs.count();
    if (timesleep > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timesleep));
    }
}
