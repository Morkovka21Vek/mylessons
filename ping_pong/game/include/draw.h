void playerWinScreen (int player, int windowWidth, int windowHeight, char background_char);
void newPointPlayer (int player,  int windowWidth, int windowHeight, char background_char);
bool drawChar (char ch, int posX, int posY, int x, int y);
char getChar  (char ch, int posX, int posY, int x, int y);

struct prediction;

void drawScreen(const square& sqr, const player& rightPl, const player& leftPl, int windowWidth, int windowHeight, int fps, const char BACKGROUND_CHAR, const prediction&, bool& redrawing);

