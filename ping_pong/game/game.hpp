#pragma once

#include <chrono>

#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/scoreBoard.hpp"
#include "gameobj/collision.hpp"
#include "screen.hpp"

class Game {
    public:
        Game() = default;
        void loop();
    private:
        Screen screen;
        ScoreBoard scboard;
        Ball ball = Ball(0.05, 0.025, 6, 3);
        Player leftPl = Player(3, 7, Playermode::keyboard, Playerpos::left);
        Player rightPl = Player(3, 7, Playermode::bot, Playerpos::right);

        static void fpsLock(std::chrono::milliseconds frameTimeMs, size_t fpscount);

        static const size_t MAXFPS;
};
