#include "include/inputs.h"
#include "include/assets.h"

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

void botTick(player& pl, const square& sqr, const prediction& pred, int windowWidth, int windowHeight) {
    pl.pos = sqr.posY - static_cast<int>(pl.height/2);
    //pl.pos -= (pred.pred - sqr.posY - static_cast<int>(pl.height/2)) / pred.predTime + (static_cast<int>(windowHeight/2) - sqr.posY) / 20 * pred.predTime;

    if (pl.pos < 0) pl.pos = 0;
    else if (pl.pos + pl.height > windowHeight) pl.pos = windowHeight - pl.height;

}

/*
  int randomVar = movePlRand();
  int randomVarModule = (randomVar < 0) ? -randomVar : randomVar;
  if (!plWin)
    leftPl.pos = leftPl.pos + (pred.pred - randomVar - leftPl.pos - leftPl.height) / (pred.predTime + randomVarModule) + randomVar;
  else
    leftPl.pos = leftPl.pos + (pred.pred - leftPl.pos - static_cast<int>(leftPl.height/2)) / (pred.predTime) + randomVar;
  
  randomVar = movePlRand();
  randomVarModule = (randomVar < 0) ? -randomVar : randomVar;
  if (!plWin)
    rightPl.pos = rightPl.pos + (pred.pred - randomVar - rightPl.pos - rightPl.height) / (pred.predTime + randomVarModule) + randomVar;
  else
    rightPl.pos = rightPl.pos + (pred.pred - rightPl.pos - static_cast<int>(rightPl.height/2)) / (pred.predTime) + randomVar;
*/

