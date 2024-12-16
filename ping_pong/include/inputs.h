#include <vector>

struct prediction {
  float pred;
  int predTime;
  std::vector<int> pathX;
  std::vector<int> pathY;
};

prediction calcPred(struct square sqrPred, int leftMargin, int rightMargin, int width, int height);
void botTick(struct player& pl, square, prediction, int windowWidth, int windowHeight);


void keyInpTick (player& pl1, char up_key1, char down_key1, player& pl2, char up_key2, char down_key2, int windowWidth, int windowHeight);


void serial_stdTick (player& pl1, char up_key1, char down_key1, player& pl2, char up_key2, char down_key2, int windowWidth, int windowHeight);


void getHttpBtnCout(player& pl1, player& pl2, int windowWidth, int windowHeight);
void initSocket();

