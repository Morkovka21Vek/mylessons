#include <vector>

struct prediction {
  float pred;
  int predTime;
  std::vector<int> pathX;
  std::vector<int> pathY;
};

prediction calcPred(struct square sqrPred, int leftMargin, int rightMargin, int width, int height); 
void botTick(struct player& pl, square, int windowWidth, int windowHeight);

