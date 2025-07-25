#include "game.hpp"
#include "gameobj/collision.hpp"
#include <format>
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
        screen.addMatrix(0, scboard.calcX(screen.getGameSize()),
                         scboard.getMatrix());
        screen.addMatrix(leftPl.getPos(), leftPl.calcX(screen.getGameSize()),
                         leftPl.getMatrix());
        screen.addMatrix(rightPl.getPos(), rightPl.calcX(screen.getGameSize()),
                         rightPl.getMatrix());
        screen.addMatrix(ball.getY(), ball.getX(), ball.getMatrix());
        screen.addText(
            0, 0,
            std::format("{}fps", (frameTimeMs > 0) ? 1000 / frameTimeMs : 0));
        screen.draw();

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
