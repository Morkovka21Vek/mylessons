#include <iostream>
#include <iomanip>
#include "include/assets.h"
#include "include/draw.h"
#include "include/inputs.h"

inline bool pathFind(const prediction&, int x, int y);

void drawScreen(const square& sqr, const player& rightPl, const player& leftPl,int windowWidth, int windowHeight,
    int fps, const char BACKGROUND_CHAR, const prediction& pred, bool& redrawing) {
  int cursorX = 0;
  int cursorY = 0;
  //static char screen_arr     [windowHeight][windowWidth];
  //static char screen_arr_old [windowHeight][windowWidth];
  static std::vector<std::vector<char>> screen_arr     (windowHeight, std::vector<char>(windowWidth, 0));
  static std::vector<std::vector<char>> screen_arr_old (windowHeight, std::vector<char>(windowWidth, 0));

  for (int y = 0; y < windowHeight; y++){
    for (int x = 0; x < windowWidth; x++){

      if ((screen_arr[y][x] = getChar(Char_ball, static_cast<int>(sqr.posX-sqr.sizeX), static_cast<int>(sqr.posY-sqr.sizeY), x, y)) != ' ') continue;

      if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) ||
          (x >= windowWidth - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height))) {
        screen_arr[y][x] = '@';
        continue;
      }

      if ((screen_arr[y][x] = getChar(Char_colon, static_cast<int>(windowWidth/2) - 2, 1, x, y)) != ' ') continue;
      if ((screen_arr[y][x] = getChar(static_cast<charsEnum>(leftPl.score + 1), static_cast<int>(windowWidth/2) - 6, 1, x, y)) != ' ')  continue;
      if ((screen_arr[y][x] = getChar(static_cast<charsEnum>(rightPl.score + 1), static_cast<int>(windowWidth/2) + 2, 1, x, y)) != ' ') continue;

      if (pathFind(pred, x, y)
        && ((sqr.speedX > 0 && rightPl.showPred) || (sqr.speedX < 0 && leftPl.showPred))) {
          screen_arr[y][x] = 'X';
          continue;
      }

      screen_arr[y][x] = BACKGROUND_CHAR;
    }
  }

  if (redrawing) {
    for (int y = 0; y < windowHeight; y++){
      std::cout << "\033[" << y+1 << ';' << 1 << 'H';
      cursorY = y;
      cursorX = 0;
      for (int x = 0; x < windowWidth; x++){
        std::cout << screen_arr[y][x];
        cursorX++;
        screen_arr_old[y][x] = screen_arr[y][x];
      }
    }
    redrawing = false;
  } else {
    for (int y = 0; y < windowHeight; y++){
      for (int x = 0; x < windowWidth; x++){
        if(screen_arr[y][x] != screen_arr_old[y][x]) {
          if(cursorY == y && !(cursorY == 0 && cursorX == 0) && x == cursorX+1) {
            std::cout << screen_arr[y][x];
            cursorX++;
          } else {
            std::cout << "\033[" << y+1 << ';' << x+1 << 'H' << screen_arr[y][x];
            cursorX = x+1;
            cursorY = y;
          }
        }
        screen_arr_old[y][x] = screen_arr[y][x];
      }
    }
  }
  std::cout << "\033[0;1H\x1B[92m" << fps << "FPS\033[0m";
  std::cout << "\033[" << windowHeight+1 << ";1H";
}


void playerWinScreen (int player, int windowWidth, int windowHeight, char background_char) {
  system("clear");

  int centerScrX = static_cast<int>(windowWidth / 2);
  int centerScrY = static_cast<int>(windowHeight / 2) - 3;

  for (int y = 0; y < windowHeight; y++){
      for (int x = 0; x < windowWidth; x++){
             if (drawChar(Char_P, centerScrX-32, centerScrY, x, y)) {}
        else if (drawChar(Char_L, centerScrX-27, centerScrY, x, y)) {}
        else if (drawChar(Char_A, centerScrX-22, centerScrY, x, y)) {}
        else if (drawChar(Char_Y, centerScrX-17, centerScrY, x, y)) {}
        else if (drawChar(Char_E, centerScrX-12, centerScrY, x, y)) {}
        else if (drawChar(Char_R, centerScrX-7, centerScrY, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(player + 1), centerScrX+2, centerScrY, x, y)) {}
        else if (drawChar(Char_W, centerScrX+10, centerScrY+1, x, y)) {}
        else if (drawChar(Char_I, centerScrX+16, centerScrY, x, y)) {}
        else if (drawChar(Char_N, centerScrX+21, centerScrY, x, y)) {}
        else std::cout << background_char;
      }
      std::cout << std::endl;
  }
}

void newPointPlayer(int player, int windowWidth, int windowHeight, char background_char) {
  system("clear");

  int centerScrX = static_cast<int>(windowWidth / 2);
  int centerScrY = static_cast<int>(windowHeight / 2) - 3;

  for (int y = 0; y < windowHeight; y++){
      for (int x = 0; x < windowWidth; x++){
             if (drawChar(Char_P, centerScrX-35, centerScrY, x, y)) {}
        else if (drawChar(Char_L, centerScrX-30, centerScrY, x, y)) {}
        else if (drawChar(Char_A, centerScrX-25, centerScrY, x, y)) {}
        else if (drawChar(Char_Y, centerScrX-20, centerScrY, x, y)) {}
        else if (drawChar(Char_E, centerScrX-15, centerScrY, x, y)) {}
        else if (drawChar(Char_R, centerScrX-10, centerScrY, x, y)) {}
        else if (drawChar(static_cast<charsEnum>(player + 1), centerScrX-2, centerScrY, x, y)) {}
        else if (drawChar(Char_plus, centerScrX+8, centerScrY, x, y)) {}
        else if (drawChar(Char_1, centerScrX+15, centerScrY, x, y)) {}
        else if (drawChar(Char_P, centerScrX+25, centerScrY, x, y)) {}
        else if (drawChar(Char_O, centerScrX+30, centerScrY, x, y)) {}
        else if (drawChar(Char_I, centerScrX+35, centerScrY, x, y)) {}
        else if (drawChar(Char_N, centerScrX+40, centerScrY, x, y)) {}
        else if (drawChar(Char_T, centerScrX+45, centerScrY, x, y)) {}
        else std::cout << background_char;
      }
      std::cout << std::endl;
  }
}

bool drawChar (enum charsEnum chEn, int posX, int posY, int x, int y) {
  int width=0, height=0;
  getSizeCh(chEn, width, height);

  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    char outCh = getSymbolCh (chEn, x - posX, y - posY);
    if (outCh != ' ') {
      std::cout << outCh;
      return true;
    }
  }
  return false;
}

char getChar (enum charsEnum chEn, int posX, int posY, int x, int y) {
  int width=0, height=0;
  getSizeCh(chEn, width, height);

  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    return getSymbolCh(chEn, x - posX, y - posY);
  }
  return ' ';
}

inline bool pathFind(const prediction& pred, int x, int y) {
  for (int i=0; i < static_cast<int>(pred.pathX.size()); i++) {
    if (pred.pathX[i] == x && pred.pathY[i] == y) return 1;
  }
  return 0;
}
