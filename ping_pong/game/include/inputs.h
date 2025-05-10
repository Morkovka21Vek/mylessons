#ifndef INCLUDE_INPUTS_H
#define INCLUDE_INPUTS_H
#include <vector>

struct prediction {
    float pred;
    int predTime;
    std::vector<int> pathX;
    std::vector<int> pathY;
};

prediction calcPred(struct square sqrPred, int leftMargin, int rightMargin,
                    int width, int height);
void botTick(struct player &pl, const square &, const prediction &,
             int windowWidth, int windowHeight);

std::pair<bool, char> kbhit();
void keyInpTick(player &pl, int windowWidth, int windowHeight);

void serial_stdTick(player &pl, int windowWidth, int windowHeight);

void getHttpBtnCout(int &sock, player &pl, int windowWidth, int windowHeight);
void initSocket(int &sock);
#endif
