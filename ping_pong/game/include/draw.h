void playerWinScreen (int player, int windowWidth, int windowHeight, char background_char);
void newPointPlayer (int player,  int windowWidth, int windowHeight, char background_char);
char getChar  (char ch, int posX, int posY, int x, int y);
void drawText (std::string text, int spaceSize, int windowWidth, int windowHeight, const char background_char);
struct prediction;

void drawScreen(const square& sqr, const player& rightPl, const player& leftPl, int windowWidth, int windowHeight, int fps, const char BACKGROUND_CHAR, const prediction&, bool& redrawing);

