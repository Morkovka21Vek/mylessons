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
  //const char *screen_arr      = new char[windowHeight][windowWidth];
  //const char *screen_arr_old  = new char[windowHeight][windowWidth];
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

      if ((screen_arr[y][x] = getChar(':', static_cast<int>(windowWidth/2) - 1, 1, x, y)) != ' ') continue;
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
  std::string string_fps = std::to_string(fps) + "FPS";
  std::cout << "\033[0;1H";
  for (size_t i = 0; i < string_fps.length(); i++) {
    if (screen_arr[0][i] != BACKGROUND_CHAR) std::cout << "\033[0;47m";
    else std::cout << "\033[0;40m";
    std::cout << "\x1B[92m" << string_fps[i];
  }
  std::cout << "\033[0m";
  std::cout << "\033[" << windowHeight+1 << ";1H" << std::flush;
}

void drawText (const std::string text, const int spaceSize, const int windowWidth, const int windowHeight, const char background_char) {
  int widthText = 0;

  for (char ch : text) {
    int width=0, height=0;
    getSizeCh(ch, width, height);
    widthText += width + spaceSize;
  }

  for (int y = 0; y < windowHeight; y++) {
    std::cout << "\033[" << y+1 << ";1H";

    for (int x = 0; x < windowWidth; x++) {
      int drawPosX = static_cast<int> (windowWidth / 2 - widthText / 2);
      char drawCh = background_char;

      for (char ch : text) {
        int width=0, height=0;
        getSizeCh(ch, width, height);

        char tempCh;
        if ((tempCh = getChar(ch, drawPosX, static_cast<int> (windowHeight / 2 - height / 2), x, y)) != ' ') {
          drawCh = tempCh;
          break;
        }
        drawPosX += width + spaceSize;
      }
      std::cout << drawCh;
    }
  }
  std::cout << std::endl;
}

void playerWinScreen (int player, int windowWidth, int windowHeight, char background_char) {
  std::string text = "PLAYER ";
  text += std::to_string(player);
  text += " WIN";
  drawText (text, 2, windowWidth, windowHeight, background_char);
}

void newPointPlayer(int player, int windowWidth, int windowHeight, char background_char) {
  std::string text = "PLAYER ";
  text += std::to_string(player);
  text += "  +1 POINT";
  drawText (text, 2, windowWidth, windowHeight, background_char);
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
