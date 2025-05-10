#include "include/assets.h"
#include "include/inputs.h"

prediction calcPred(square sqrPred, int leftMargin, int rightMargin,
                    int windowWidth, int windowHeight) {
    prediction pred = {0, 0};

    while (1) {
        if (sqrPred.posX + sqrPred.sizeX >= windowWidth - rightMargin - 1 &&
            sqrPred.speedX > 0)
            break;
        else if (sqrPred.posX - sqrPred.sizeX <= leftMargin &&
                 sqrPred.speedX < 0)
            break;

        pred.predTime++;
        pred.pathX.push_back(static_cast<int>(sqrPred.posX));
        pred.pathY.push_back(static_cast<int>(sqrPred.posY));

        sqrPred.posX += sqrPred.speedX;
        sqrPred.posY += sqrPred.speedY;

        if (sqrPred.posY - sqrPred.sizeY <= 0)
            sqrPred.speedY *= -1;
        else if (sqrPred.posY + sqrPred.sizeY >= windowHeight - 1)
            sqrPred.speedY *= -1;
    }

    pred.pred = sqrPred.posY;
    return pred;
}

void botTick(player &pl, const square &sqr, const prediction &pred,
             int windowWidth, int windowHeight) {
    // pl.pos = sqr.posY - static_cast<int>(pl.height/2);
    pl.pos = pl.pos + (pred.pred - pl.pos - static_cast<int>(pl.height / 2)) /
                          pred.predTime;

    if (pl.pos < 0)
        pl.pos = 0;
    else if (pl.pos + pl.height > windowHeight)
        pl.pos = windowHeight - pl.height;
}
