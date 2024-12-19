enum charsEnum {
  Char_ball,
  Char_0,
  Char_1,
  Char_2,
  Char_3,
  Char_colon, //двоеточие
  Char_P,
  Char_L,
  Char_A,
  Char_Y,
  Char_E,
  Char_R,
  Char_O,
  Char_I,
  Char_N,
  Char_T,
  Char_W,
  Char_plus
};
char getSymbolCh (enum charsEnum ch, int, int);
void getSizeCh (enum charsEnum ch, int& xSize, int& ySize);

struct square {
  float posX;
  float posY;
  float speedX;
  float speedY;
  int sizeX;
  int sizeY;
};

struct player {
  int pos;
  int score;
  const int width;
  const int height;
  bool showPred;
};

