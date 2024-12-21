#include <vector>

struct prediction {
  float pred;
  int predTime;
  std::vector<int> pathX;
  std::vector<int> pathY;
};

prediction calcPred(struct square sqrPred, int leftMargin, int rightMargin, int width, int height);
void botTick(struct player& pl, const square&, const prediction&, int windowWidth, int windowHeight);


void keyInpTick (player& pl, char up_key, char down_key, int windowWidth, int windowHeight);


void serial_stdTick (player& pl, char up_key, char down_key, int windowWidth, int windowHeight);


void getHttpBtnCout(int& sock, player& pl, int windowWidth, int windowHeight);
void initSocket(int& sock);

