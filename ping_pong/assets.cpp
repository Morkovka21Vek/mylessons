#include "assets.h"

const char zeroChar[6][4] = {
  {'0', '0', '0', '0'},
  {'0', ' ', ' ', '0'},
  {'0', ' ', ' ', '0'},
  {'0', ' ', ' ', '0'},
  {'0', ' ', ' ', '0'},
  {'0', '0', '0', '0'}
};

const char oneChar[6][4] = {
  {' ', '1', '1', ' '},
  {' ', '1', '1', ' '},
  {' ', '1', '1', ' '},
  {' ', '1', '1', ' '},
  {' ', '1', '1', ' '},
  {' ', '1', '1', ' '}
};

const char twoChar[6][4] = {
  {'2', '2', '2', '2'},
  {' ', ' ', ' ', '2'},
  {'2', '2', '2', '2'},
  {'2', ' ', ' ', ' '},
  {'2', ' ', ' ', ' '},
  {'2', '2', '2', '2'}
};

const char threeChar[6][4] = {
  {'3', '3', '3', '3'},
  {' ', ' ', ' ', '3'},
  {'3', '3', '3', '3'},
  {' ', ' ', ' ', '3'},
  {' ', ' ', ' ', '3'},
  {'3', '3', '3', '3'}
};

const char colonChar[6][4] = {
  {' ', '#', '#', ' '},
  {' ', '#', '#', ' '},
  {' ', ' ', ' ', ' '},
  {' ', ' ', ' ', ' '},
  {' ', '#', '#', ' '},
  {' ', '#', '#', ' '}
};

const char ballChar[5][9] = {
  {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
  {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
  {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
  {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
  {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
};

const char Pchar[6][4] = {
  {'P', 'P', 'P', ' '},
  {'P', ' ', ' ', 'P'},
  {'P', 'P', 'P', ' '},
  {'P', ' ', ' ', ' '},
  {'P', ' ', ' ', ' '},
  {'P', ' ', ' ', ' '}
};

const char Lchar[6][4] = {
  {'L', ' ', ' ', ' '},
  {'L', ' ', ' ', ' '},
  {'L', ' ', ' ', ' '},
  {'L', ' ', ' ', ' '},
  {'L', ' ', ' ', ' '},
  {'L', 'L', 'L', 'L'}
};

const char Achar[6][4] = {
  {' ', 'A', 'A', ' '},
  {'A', ' ', ' ', 'A'},
  {'A', ' ', ' ', 'A'},
  {'A', 'A', 'A', 'A'},
  {'A', ' ', ' ', 'A'},
  {'A', ' ', ' ', 'A'}
};

const char Ychar[6][4] = {
  {'Y', ' ', ' ', 'Y'},
  {' ', 'Y', 'Y', ' '},
  {' ', 'Y', 'Y', ' '},
  {' ', 'Y', 'Y', ' '},
  {' ', 'Y', 'Y', ' '},
  {' ', 'Y', 'Y', ' '}
};

const char Echar[6][4] = {
  {'E', 'E', 'E', 'E'},
  {'E', ' ', ' ', ' '},
  {'E', 'E', 'E', 'E'},
  {'E', ' ', ' ', ' '},
  {'E', ' ', ' ', ' '},
  {'E', 'E', 'E', 'E'}
};

const char Rchar[6][4] = {
  {'R', 'R', 'R', ' '},
  {'R', ' ', ' ', 'R'},
  {'R', 'R', 'R', ' '},
  {'R', 'R', ' ', ' '},
  {'R', ' ', 'R', ' '},
  {'R', ' ', ' ', 'R'}
};

const char Ochar[6][4] = {
  {' ', 'O', 'O', ' '},
  {'O', ' ', ' ', 'O'},
  {'O', ' ', ' ', 'O'},
  {'O', ' ', ' ', 'O'},
  {'O', ' ', ' ', 'O'},
  {' ', 'O', 'O', ' '}
};

const char Ichar[6][4] = {
  {'I', 'I', 'I', 'I'},
  {' ', 'I', 'I', ' '},
  {' ', 'I', 'I', ' '},
  {' ', 'I', 'I', ' '},
  {' ', 'I', 'I', ' '},
  {'I', 'I', 'I', 'I'}
};

const char Nchar[6][4] = {
  {'N', ' ', ' ', 'N'},
  {'N', 'N', ' ', 'N'},
  {'N', 'N', ' ', 'N'},
  {'N', ' ', 'N', 'N'},
  {'N', ' ', 'N', 'N'},
  {'N', ' ', ' ', 'N'}
};

const char Tchar[6][4] = {
  {'T', 'T', 'T', 'T'},
  {' ', 'T', 'T', ' '},
  {' ', 'T', 'T', ' '},
  {' ', 'T', 'T', ' '},
  {' ', 'T', 'T', ' '},
  {' ', 'T', 'T', ' '}
};

const char Wchar[5][5] = {
  {'W', ' ', 'W', ' ', 'W'},
  {'W', ' ', 'W', ' ', 'W'},
  {'W', ' ', 'W', ' ', 'W'},
  {' ', 'W', ' ', 'W', ' '},
  {' ', 'W', ' ', 'W', ' '},
};


const char plusChar[6][6] = {
  {' ', ' ', '+', '+', ' ', ' '},
  {' ', ' ', '+', '+', ' ', ' '},
  {'+', '+', '+', '+', '+', '+'},
  {'+', '+', '+', '+', '+', '+'},
  {' ', ' ', '+', '+', ' ', ' '},
  {' ', ' ', '+', '+', ' ', ' '}
};

char getSymbolCh (enum charsEnum ch, int x, int y) {
  char out = 'E';

  //int rows = sizeof(tempCh)/ sizeof(tempChar[0]);
  //int cols = sizeof(tempCh[0])/ sizeof(int);
  switch (ch) {
    case Char_ball: out = ballChar[y][x]; break;
    case Char_0: out = zeroChar[y][x]; break;
    case Char_1: out = oneChar[y][x]; break;
    case Char_2: out = twoChar[y][x]; break;
    case Char_3: out = threeChar[y][x]; break;
    case Char_colon: out = colonChar[y][x]; break;
    case Char_P: out = Pchar[y][x]; break;
    case Char_L: out = Lchar[y][x]; break;
    case Char_A: out = Achar[y][x]; break;
    case Char_Y: out = Ychar[y][x]; break;
    case Char_E: out = Echar[y][x]; break;
    case Char_R: out = Rchar[y][x]; break;
    case Char_O: out = Ochar[y][x]; break;
    case Char_I: out = Ichar[y][x]; break;
    case Char_N: out = Nchar[y][x]; break;
    case Char_T: out = Tchar[y][x]; break;
    case Char_W: out = Wchar[y][x]; break;
    case Char_plus: out = plusChar[y][x]; break;
  }
  return out;
}

void getSizeCh (enum charsEnum ch, int& xSize, int& ySize) {
  //int rows = sizeof(tempCh)/ sizeof(tempChar[0]);
  //int cols = sizeof(tempCh[0])/ sizeof(int);
  switch (ch) {
    case Char_ball:
      xSize = sizeof(ballChar[0])/ sizeof(char);
      ySize = sizeof(ballChar)/ sizeof(ballChar[0]); break;
    case Char_0:
      xSize = sizeof(zeroChar[0])/ sizeof(char);
      ySize = sizeof(zeroChar)/ sizeof(zeroChar[0]); break;
    case Char_1:
      xSize = sizeof(oneChar[0])/ sizeof(char);
      ySize = sizeof(oneChar)/ sizeof(oneChar[0]); break;
    case Char_2:
      xSize = sizeof(twoChar[0])/ sizeof(char);
      ySize = sizeof(twoChar)/ sizeof(twoChar[0]); break;
    case Char_3:
      xSize = sizeof(threeChar[0])/ sizeof(char);
      ySize = sizeof(threeChar)/ sizeof(threeChar[0]); break;
    case Char_colon:
      xSize = sizeof(colonChar[0])/ sizeof(char);
      ySize = sizeof(colonChar)/ sizeof(colonChar[0]); break;
    case Char_P:
      xSize = sizeof(Pchar[0])/ sizeof(char);
      ySize = sizeof(Pchar)/ sizeof(Pchar[0]); break;
    case Char_L:
      xSize = sizeof(Lchar[0])/ sizeof(char);
      ySize = sizeof(Lchar)/ sizeof(Lchar[0]); break;
    case Char_A:
      xSize = sizeof(Achar[0])/ sizeof(char);
      ySize = sizeof(Achar)/ sizeof(Achar[0]); break;
    case Char_Y:
      xSize = sizeof(Ychar[0])/ sizeof(char);
      ySize = sizeof(Ychar)/ sizeof(Ychar[0]); break;
    case Char_E:
      xSize = sizeof(Echar[0])/ sizeof(char);
      ySize = sizeof(Echar)/ sizeof(Echar[0]); break;
    case Char_R:
      xSize = sizeof(Echar[0])/ sizeof(char);
      ySize = sizeof(Echar)/ sizeof(Echar[0]); break;
    case Char_O:
      xSize = sizeof(Ochar[0])/ sizeof(char);
      ySize = sizeof(Ochar)/ sizeof(Ochar[0]); break;
    case Char_I:
      xSize = sizeof(Ichar[0])/ sizeof(char);
      ySize = sizeof(Ichar)/ sizeof(Ichar[0]); break;
    case Char_N:
      xSize = sizeof(Nchar[0])/ sizeof(char);
      ySize = sizeof(Nchar)/ sizeof(Nchar[0]); break;
    case Char_T:
      xSize = sizeof(Tchar[0])/ sizeof(char);
      ySize = sizeof(Tchar)/ sizeof(Tchar[0]); break;
    case Char_W:
      xSize = sizeof(Wchar[0])/ sizeof(char);
      ySize = sizeof(Wchar)/ sizeof(Wchar[0]); break;
    case Char_plus:
      xSize = sizeof(plusChar[0])/ sizeof(char);
      ySize = sizeof(plusChar)/ sizeof(plusChar[0]); break;
  }
}

