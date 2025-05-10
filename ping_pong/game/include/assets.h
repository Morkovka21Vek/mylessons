#ifndef INCLUDE_ASSETS_H
#define INCLUDE_ASSETS_H
char getSymbolCh(char, int, int);
void getSizeCh(char, int &xSize, int &ySize);

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
    int mode;
    char up_key;
    char down_key;
};

enum player_mode { bot_pl_mode, keyboard_pl_mode, std_pl_mode, http_pl_mode };
#endif
