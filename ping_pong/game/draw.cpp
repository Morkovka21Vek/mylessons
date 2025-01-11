#include <iostream>
#include <iomanip>
#include <string>
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

      if ((screen_arr[y][x] = getChar(9, static_cast<int>(sqr.posX-sqr.sizeX), static_cast<int>(sqr.posY-sqr.sizeY), x, y)) != ' ') continue;

      if ((x < leftPl.width && (y >= leftPl.pos && y < leftPl.pos + leftPl.height)) ||
          (x >= windowWidth - rightPl.width && (y >= rightPl.pos && y < rightPl.pos + rightPl.height))) {
        screen_arr[y][x] = '@';
        continue;
      }

      if ((screen_arr[y][x] = getChar(':', static_cast<int>(windowWidth/2) - 2, 1, x, y)) != ' ') continue;
      if ((screen_arr[y][x] = getChar(leftPl.score + '0', static_cast<int>(windowWidth/2) - 6, 1, x, y)) != ' ')  continue;
      if ((screen_arr[y][x] = getChar(rightPl.score + '0', static_cast<int>(windowWidth/2) + 2, 1, x, y)) != ' ') continue;

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

//void drawText (std::string text) {
//  int widthText = 0;
//  int width=0, height=0;
//
//  for (int i = 0; i < ; i++) {
//    getSizeCh(, width, height);
//    widthText += width;
//  }
//}

void playerWinScreen (int player, int windowWidth, int windowHeight, char background_char) {
  system("clear");

  int centerScrX = static_cast<int>(windowWidth / 2);
  int centerScrY = static_cast<int>(windowHeight / 2) - 3;

  for (int y = 0; y < windowHeight; y++){
      for (int x = 0; x < windowWidth; x++){
             if (drawChar('P', centerScrX-32, centerScrY, x, y)) {}
        else if (drawChar('L', centerScrX-27, centerScrY, x, y)) {}
        else if (drawChar('A', centerScrX-22, centerScrY, x, y)) {}
        else if (drawChar('Y', centerScrX-17, centerScrY, x, y)) {}
        else if (drawChar('E', centerScrX-12, centerScrY, x, y)) {}
        else if (drawChar('R', centerScrX-7, centerScrY, x, y)) {}
        else if (drawChar(player + '0', centerScrX+2, centerScrY, x, y)) {}
        else if (drawChar('W', centerScrX+10, centerScrY+1, x, y)) {}
        else if (drawChar('I', centerScrX+16, centerScrY, x, y)) {}
        else if (drawChar('N', centerScrX+21, centerScrY, x, y)) {}
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
             if (drawChar('P', centerScrX-35, centerScrY, x, y)) {}
        else if (drawChar('L', centerScrX-30, centerScrY, x, y)) {}
        else if (drawChar('A', centerScrX-25, centerScrY, x, y)) {}
        else if (drawChar('Y', centerScrX-20, centerScrY, x, y)) {}
        else if (drawChar('E', centerScrX-15, centerScrY, x, y)) {}
        else if (drawChar('R', centerScrX-10, centerScrY, x, y)) {}
        else if (drawChar(player + '0', centerScrX-2, centerScrY, x, y)) {}
        else if (drawChar('+', centerScrX+8, centerScrY, x, y)) {}
        else if (drawChar('1', centerScrX+15, centerScrY, x, y)) {}
        else if (drawChar('P', centerScrX+25, centerScrY, x, y)) {}
        else if (drawChar('O', centerScrX+30, centerScrY, x, y)) {}
        else if (drawChar('I', centerScrX+35, centerScrY, x, y)) {}
        else if (drawChar('N', centerScrX+40, centerScrY, x, y)) {}
        else if (drawChar('T', centerScrX+45, centerScrY, x, y)) {}
        else std::cout << background_char;
      }
      std::cout << std::endl;
  }
}

bool drawChar (char ch, int posX, int posY, int x, int y) {
  int width=0, height=0;
  getSizeCh(ch, width, height);

  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    char outCh = getSymbolCh (ch, x - posX, y - posY);
    if (outCh != ' ') {
      std::cout << outCh;
      return true;
    }
  }
  return false;
}

char getChar (char ch, int posX, int posY, int x, int y) {
  int width=0, height=0;
  getSizeCh(ch, width, height);

  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    return getSymbolCh(ch, x - posX, y - posY);
  }
  return ' ';
}

inline bool pathFind(const prediction& pred, int x, int y) {
  for (int i=0; i < static_cast<int>(pred.pathX.size()); i++) {
    if (pred.pathX[i] == x && pred.pathY[i] == y) return 1;
  }
  return 0;
}
