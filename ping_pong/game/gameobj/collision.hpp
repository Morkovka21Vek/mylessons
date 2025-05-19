#pragma once
#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/scoreBoard.hpp"

class CollisionSystem {
public:
    static void handleAllCollisions(Ball& ball, const Player& leftPl, 
                                  const Player& rightPl, struct scrsize ws, 
                                  const ScoreBoard& scoreBoard);
    
private:
    static void handleWallCollision(Ball& ball, const scrsize ws);
    
    static void handlePaddleCollision(Ball& ball, const Player& player, const scrsize ws);

    static void handleRightPaddleCollision(Ball& ball, const Player& player, const scrsize ws);
    static void handleLeftPaddleCollision(Ball& ball, const Player& player, const scrsize ws);
};
