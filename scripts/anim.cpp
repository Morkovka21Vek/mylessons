#include <chrono>
#include <iomanip>
#include <iostream>
#include <thread>

const int speedX = 1;
const int speedY = 1;
const int sizeX = 2;
const int sizeY = 1;

void draw(int x, int y) {
    if ((x >= posX - sizeX && x <= posX + sizeX) &&
        (y >= posY - sizeY && y <= posY + sizeY))
        std::cout << '#';
    else
        std::cout << '-';
}
int main() {
    using namespace std::this_thread;
    using namespace std::chrono;

    int screenX = 185;
    int screenY = 45;
    int posX = 3;
    int posY = 3;

    while (true) {
        for (int y = 0; y < screenY; y++) {
            for (int x = 0; x < screenX; x++) {
                draw(x, y);
            }
            std::cout << std::endl;
        }

        posX += speedX;
        posY += speedY;

        if (posX - sizeX <= 1)
            speedX *= -1;
        if (posX + sizeX >= screenX - 1)
            speedX *= -1;
        if (posY - sizeY <= 1)
            speedY *= -1;
        if (posY + sizeY >= screenY - 1)
            speedY *= -1;

        sleep_for(nanoseconds(100 * 1000000));
    }
    return 0;
}
