#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/collision.hpp"
#include "gameobj/scoreBoard.hpp"

void CollisionSystem::handleAllCollisions(Ball& ball, const Player& leftPl,
                              const Player& rightPl, struct scrsize ws,
                              const ScoreBoard& scoreBoard) {
    handleWallCollision(ball, ws);
    handlePaddleCollision(ball, leftPl, ws);
    handlePaddleCollision(ball, rightPl, ws);
    //handleGoalCollision(ball, ws, scoreBoard);
}

void CollisionSystem::handleWallCollision(Ball& ball, const scrsize ws) {
    if (ball.getY() <= 0) {
        ball.setY(0);
        ball.reverseY();
    }
    else if (ball.getY() + ball.getHeight() >= ws.height) {
        ball.setY(ws.height - ball.getHeight());
        ball.reverseY();
    }
}

void CollisionSystem::handlePaddleCollision(Ball& ball, const Player& player, const scrsize ws) {
    switch (player.getPlPosX()) {
        case Playerpos::left:  handleLeftPaddleCollision(ball, player, ws);  break;
        case Playerpos::right: handleRightPaddleCollision(ball, player, ws); break;
    }
}

void CollisionSystem::handleLeftPaddleCollision(Ball& ball, const Player& player, const scrsize ws) {
    if (ball.getX() <= player.calcX(ws) + player.getWidth()) {
        if (ball.getY() + ball.getHeight() >= player.getPos() && ball.getY() <= player.getPos() + player.getHeight()) {
            //ball.setX(player.calcX(ws) + player.getWidth());
            ball.reverseX();
        }
    }
}

void CollisionSystem::handleRightPaddleCollision(Ball& ball, const Player& player, const scrsize ws) {
    if (ball.getX() + ball.getWidth() >= player.calcX(ws)) {
        if (ball.getY() + ball.getHeight() >= player.getPos() && ball.getY() <= player.getPos() + player.getHeight()) {
            //ball.setX(player.calcX(ws) - ball.getWidth());
            ball.reverseX();
        }
    }
}
