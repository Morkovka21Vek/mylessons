#include "assets.hpp"

#define char_size(ch, xsize, ysize)                                            \
    xsize = sizeof(ch[0]) / sizeof(char);                                      \
    ysize = sizeof(ch) / sizeof(ch[0]);

static const char zeroChar[6][4] = {{'0', '0', '0', '0'}, {'0', ' ', ' ', '0'},
                                    {'0', ' ', ' ', '0'}, {'0', ' ', ' ', '0'},
                                    {'0', ' ', ' ', '0'}, {'0', '0', '0', '0'}};

static const char oneChar[6][2] = {{'1', '1'}, {'1', '1'}, {'1', '1'},
                                   {'1', '1'}, {'1', '1'}, {'1', '1'}};

static const char twoChar[6][4] = {{'2', '2', '2', '2'}, {' ', ' ', ' ', '2'},
                                   {'2', '2', '2', '2'}, {'2', ' ', ' ', ' '},
                                   {'2', ' ', ' ', ' '}, {'2', '2', '2', '2'}};

static const char threeChar[6][4] = {
    {'3', '3', '3', '3'}, {' ', ' ', ' ', '3'}, {'3', '3', '3', '3'},
    {' ', ' ', ' ', '3'}, {' ', ' ', ' ', '3'}, {'3', '3', '3', '3'}};

static const char colonChar[6][2] = {{'#', '#'}, {'#', '#'}, {' ', ' '},
                                     {' ', ' '}, {'#', '#'}, {'#', '#'}};

static const char ballChar[5][9] = {
    {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
    {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {' ', '#', '#', '#', '#', '#', '#', '#', ' '},
    {' ', ' ', ' ', '#', '#', '#', ' ', ' ', ' '},
};

static const char Pchar[6][4] = {{'P', 'P', 'P', ' '}, {'P', ' ', ' ', 'P'},
                                 {'P', 'P', 'P', ' '}, {'P', ' ', ' ', ' '},
                                 {'P', ' ', ' ', ' '}, {'P', ' ', ' ', ' '}};

static const char Lchar[6][4] = {{'L', ' ', ' ', ' '}, {'L', ' ', ' ', ' '},
                                 {'L', ' ', ' ', ' '}, {'L', ' ', ' ', ' '},
                                 {'L', ' ', ' ', ' '}, {'L', 'L', 'L', 'L'}};

static const char Achar[6][4] = {{' ', 'A', 'A', ' '}, {'A', ' ', ' ', 'A'},
                                 {'A', ' ', ' ', 'A'}, {'A', 'A', 'A', 'A'},
                                 {'A', ' ', ' ', 'A'}, {'A', ' ', ' ', 'A'}};

static const char Ychar[6][4] = {{'Y', ' ', ' ', 'Y'}, {' ', 'Y', 'Y', ' '},
                                 {' ', 'Y', 'Y', ' '}, {' ', 'Y', 'Y', ' '},
                                 {' ', 'Y', 'Y', ' '}, {' ', 'Y', 'Y', ' '}};

static const char Echar[6][4] = {{'E', 'E', 'E', 'E'}, {'E', ' ', ' ', ' '},
                                 {'E', 'E', 'E', 'E'}, {'E', ' ', ' ', ' '},
                                 {'E', ' ', ' ', ' '}, {'E', 'E', 'E', 'E'}};

static const char Rchar[6][4] = {{'R', 'R', 'R', ' '}, {'R', ' ', ' ', 'R'},
                                 {'R', 'R', 'R', ' '}, {'R', 'R', ' ', ' '},
                                 {'R', ' ', 'R', ' '}, {'R', ' ', ' ', 'R'}};

static const char Ochar[6][4] = {{' ', 'O', 'O', ' '}, {'O', ' ', ' ', 'O'},
                                 {'O', ' ', ' ', 'O'}, {'O', ' ', ' ', 'O'},
                                 {'O', ' ', ' ', 'O'}, {' ', 'O', 'O', ' '}};

static const char Ichar[6][4] = {{'I', 'I', 'I', 'I'}, {' ', 'I', 'I', ' '},
                                 {' ', 'I', 'I', ' '}, {' ', 'I', 'I', ' '},
                                 {' ', 'I', 'I', ' '}, {'I', 'I', 'I', 'I'}};

static const char Nchar[6][4] = {{'N', ' ', ' ', 'N'}, {'N', 'N', ' ', 'N'},
                                 {'N', 'N', ' ', 'N'}, {'N', ' ', 'N', 'N'},
                                 {'N', ' ', 'N', 'N'}, {'N', ' ', ' ', 'N'}};

static const char Tchar[6][4] = {{'T', 'T', 'T', 'T'}, {' ', 'T', 'T', ' '},
                                 {' ', 'T', 'T', ' '}, {' ', 'T', 'T', ' '},
                                 {' ', 'T', 'T', ' '}, {' ', 'T', 'T', ' '}};

static const char Wchar[5][5] = {
    {'W', ' ', 'W', ' ', 'W'}, {'W', ' ', 'W', ' ', 'W'},
    {'W', ' ', 'W', ' ', 'W'}, {' ', 'W', ' ', 'W', ' '},
    {' ', 'W', ' ', 'W', ' '},
};

static const char plusChar[6][6] = {
    {' ', ' ', '+', '+', ' ', ' '}, {' ', ' ', '+', '+', ' ', ' '},
    {'+', '+', '+', '+', '+', '+'}, {'+', '+', '+', '+', '+', '+'},
    {' ', ' ', '+', '+', ' ', ' '}, {' ', ' ', '+', '+', ' ', ' '}};

char getSymbolCh(char ch, int x, int y) {
    char out = 'E';

    switch (ch) {
    case 9:
        out = ballChar[y][x];
        break; // шарик
    case '0':
        out = zeroChar[y][x];
        break;
    case '1':
        out = oneChar[y][x];
        break;
    case '2':
        out = twoChar[y][x];
        break;
    case '3':
        out = threeChar[y][x];
        break;
    case ':':
        out = colonChar[y][x];
        break;
    case 'P':
        out = Pchar[y][x];
        break;
    case 'L':
        out = Lchar[y][x];
        break;
    case 'A':
        out = Achar[y][x];
        break;
    case 'Y':
        out = Ychar[y][x];
        break;
    case 'E':
        out = Echar[y][x];
        break;
    case 'R':
        out = Rchar[y][x];
        break;
    case 'O':
        out = Ochar[y][x];
        break;
    case 'I':
        out = Ichar[y][x];
        break;
    case 'N':
        out = Nchar[y][x];
        break;
    case 'T':
        out = Tchar[y][x];
        break;
    case 'W':
        out = Wchar[y][x];
        break;
    case '+':
        out = plusChar[y][x];
        break;
    case ' ':
        out = ' ';
        break;
    }
    return out;
}

void getSizeCh(char ch, int &xSize, int &ySize) {
    switch (ch) {
    case 9:
        char_size(ballChar, xSize, ySize);
        break; // шарик
    case '0':
        char_size(zeroChar, xSize, ySize);
        break;
    case '1':
        char_size(oneChar, xSize, ySize);
        break;
    case '2':
        char_size(twoChar, xSize, ySize);
        break;
    case '3':
        char_size(threeChar, xSize, ySize);
        break;
    case ':':
        char_size(colonChar, xSize, ySize);
        break;
    case 'P':
        char_size(Pchar, xSize, ySize);
        break;
    case 'L':
        char_size(Lchar, xSize, ySize);
        break;
    case 'A':
        char_size(Achar, xSize, ySize);
        break;
    case 'Y':
        char_size(Ychar, xSize, ySize);
        break;
    case 'E':
        char_size(Echar, xSize, ySize);
        break;
    case 'R':
        char_size(Rchar, xSize, ySize);
        break;
    case 'O':
        char_size(Ochar, xSize, ySize);
        break;
    case 'I':
        char_size(Ichar, xSize, ySize);
        break;
    case 'N':
        char_size(Nchar, xSize, ySize);
        break;
    case 'T':
        char_size(Tchar, xSize, ySize);
        break;
    case 'W':
        char_size(Wchar, xSize, ySize);
        break;
    case '+':
        char_size(plusChar, xSize, ySize);
        break;
    case ' ':
        xSize = 1;
        ySize = 1;
        break;
    }
}
