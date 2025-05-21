#pragma once
#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/scoreBoard.hpp"

class CollisionSystem {
  public:
    static void handleAllCollisions(Ball &, Player &leftPl, Player &rightPl,
                                    struct scrsize ws, ScoreBoard &);

  private:
    static void handleWallCollision(Ball &ball, const scrsize ws);

    static void handlePaddleCollision(Ball &ball, const Player &player,
                                      const scrsize ws);

    static void handleRightPaddleCollision(Ball &ball, const Player &player,
                                           const scrsize ws);
    static void handleLeftPaddleCollision(Ball &ball, const Player &player,
                                          const scrsize ws);

    static void handleGoalCollision(Ball &, const scrsize, ScoreBoard &,
                                    Player &, Player &);
    static void resetPos(Ball &, Player &, Player &, const scrsize ws);
};
