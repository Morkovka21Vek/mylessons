#include <iostream>
#include "assets.h"
#include "draw.h"

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
  char outCh = ' ';

  int width=0, height=0;
  getSizeCh(chEn, width, height);

  if (x >= posX && x < posX + width && y >= posY && y < posY + height) {
    outCh = getSymbolCh (chEn, x - posX, y - posY);
    if (outCh != ' ') {
      std::cout << outCh;
      return true;
    }
  }
  return false;
}
