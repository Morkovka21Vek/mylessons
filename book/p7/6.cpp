#include <ctime>
#include <iostream>

enum class Suit { clubs, diamonds, hearts, spades };

const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

class card {
  private:
    int number;
    Suit suit;

  public:
    friend std::ostream &operator<<(std::ostream &os, const card &obj);

    card() = default;
    void set(int n, Suit s) {
        number = n;
        suit = s;
    }
};

std::ostream &operator<<(std::ostream &os, const card &obj) {
    if (obj.number >= 2 && obj.number <= 10)
        os << obj.number;
    else
        switch (obj.number) {
        case jack:
            os << 'J';
            break;
        case queen:
            os << 'Q';
            break;
        case king:
            os << 'K';
            break;
        case ace:
            os << 'A';
            break;
        }

    switch (obj.suit) {

    case Suit::clubs:
        os << "♣";
        break;
    case Suit::diamonds:
        os << "♦";
        break;
    case Suit::hearts:
        os << "♥";
        break;
    case Suit::spades:
        os << "♠";
        break;
    }
    return os;
}

int main() {
    card deck[52];

    for (int j = 0; j < 52; j++) {
        int num = (j % 13) + 2;

        Suit su = Suit(j / 13);

        deck[j].set(num, su);
    }

    std::cout << "Исходная колода:" << std::endl;
    for (int j = 0; j < 52; j++) {
        std::cout << deck[j] << ' ';
        if (!((j + 1) % 13))
            std::cout << std::endl;
    }

    srand(time(NULL));
    for (int j = 0; j < 52; j++) {
        int k = rand() % 52;
        card temp = deck[j];
        deck[j] = deck[k];
        deck[k] = temp;
    }

    std::cout << std::endl << "Перемешанная колода:" << std::endl;
    for (int j = 0; j < 52; j++) {
        std::cout << deck[j] << ' ';
        if (!((j + 1) % 13))
            std::cout << std::endl;
    }
    std::cout << std::endl;

    card playersCards[4][13];

    for (int loop_num = 0; loop_num < 13; loop_num++) {
        for (int pl = 0; pl < 4; pl++) {
            playersCards[pl][loop_num] = deck[loop_num * 4 + pl];
        }
    }

    std::cout << std::endl;

    for (int i = 0; i < 4; i++) {
        std::cout << "Игрок " << i + 1 << ":" << std::endl;
        for (int j = 0; j < 13; j++) {
            std::cout << playersCards[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    return 0;
}
