#include "bot.h"
#include "assets.h"

prediction calcPred(square sqrPred, int leftMargin, int rightMargin, int windowWidth, int windowHeight) {
  prediction pred = {0, 0};

  while (1) {
    if (sqrPred.posX + sqrPred.sizeX >= windowWidth - rightMargin - 1 && sqrPred.speedX > 0) break;
    else if (sqrPred.posX - sqrPred.sizeX <= leftMargin && sqrPred.speedX < 0) break;

    pred.predTime++;
    pred.pathX.push_back(static_cast<int>(sqrPred.posX));
    pred.pathY.push_back(static_cast<int>(sqrPred.posY));

    sqrPred.posX += sqrPred.speedX;
    sqrPred.posY += sqrPred.speedY;

    if (sqrPred.posY - sqrPred.sizeY <= 0)sqrPred.speedY *= -1;
    else if (sqrPred.posY + sqrPred.sizeY >= windowHeight-1)sqrPred.speedY *= -1;
  }

  pred.pred = sqrPred.posY;
  return pred;
}

//bool plWin;
//prediction pred;
void botTick(player& pl, square sqr, int windowWidth, int windowHeight) {

    pl.pos = sqr.posY - static_cast<int>(pl.height/2);

    if (pl.pos < 0) pl.pos = 0;
    else if (pl.pos + pl.height > windowHeight) pl.pos = windowHeight - pl.height;

}
