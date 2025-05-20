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
        Game();
        void loop();
    private:
        Screen screen;
        ScoreBoard scboard;
        Ball ball;
        Player leftPl;
        Player rightPl;

        void fps_lock(std::chrono::milliseconds frame_time_ms, size_t fpscount) const;

        static const size_t MAX_FPS;
};
