#include "assets.hpp"
#include "gameobj/ball.hpp"
#include "gameobj/player.hpp"
#include "gameobj/collision.hpp"
#include "gameobj/scoreBoard.hpp"

void CollisionSystem::handleAllCollisions(Ball& ball, Player& leftPl,
                              Player& rightPl, struct scrsize ws,
                              ScoreBoard& scboard) {
    handleWallCollision(ball, ws);
    handlePaddleCollision(ball, leftPl, ws);
    handlePaddleCollision(ball, rightPl, ws);
    handleGoalCollision(ball, ws, scboard, leftPl, rightPl);
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
    switch (player.getPlayerposX()) {
        case Playerpos::left:  handleLeftPaddleCollision(ball, player, ws);  break;
        case Playerpos::right: handleRightPaddleCollision(ball, player, ws); break;
    }
}

void CollisionSystem::handleLeftPaddleCollision(Ball& ball, const Player& player, const scrsize ws) {
    if (ball.getX() <= player.calcX(ws) + player.getWidth() && ball.getY() + ball.getHeight() >= player.getPos() && ball.getY() <= player.getPos() + player.getHeight()) {
        ball.setPositiveX();
    }
}

void CollisionSystem::handleRightPaddleCollision(Ball& ball, const Player& player, const scrsize ws) {
    if (ball.getX() + ball.getWidth() >= player.calcX(ws) && ball.getY() + ball.getHeight() >= player.getPos() && ball.getY() <= player.getPos() + player.getHeight()) {
        ball.setNegativeX();
    }
}

void CollisionSystem::handleGoalCollision(Ball& ball, const scrsize ws, ScoreBoard& scboard, Player& leftPl, Player& rightPl) {
    if (ball.getX() < 0) {
        scboard.addPointRight();
        resetPos(ball, leftPl, rightPl, ws);
    } else if (ball.getX() + ball.getWidth() > ws.width) {
        scboard.addPointLeft();
        resetPos(ball, leftPl, rightPl, ws);
    }
}

void CollisionSystem::resetPos(Ball& ball, Player& leftPl, Player& rightPl, const scrsize ws) {
    ball.reset(ws);
    leftPl.reset(ws);
    rightPl.reset(ws);
}
