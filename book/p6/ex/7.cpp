#include <iostream>
#include <ostream>
#include <stdexcept>

class angle {
    public:
        angle();
        angle(int dec, int min, char orientaion);

        int answerData();
        void getValues(int& dec, float& min, char& orientaion) const;

    private:
        int _dec;
        float _min;
        char _orientaion;
};

angle::angle(): _dec(0), _min(0), _orientaion('W')
{}

angle::angle(int dec, int min, char orientaion): _dec(dec), _min(min), _orientaion(orientaion)
{
    if (this->_min < 0 || this->_dec < 0)
        throw std::invalid_argument("Value error");

    switch (this->_orientaion) {
        case 'W':
        case 'E':
            if (this->_min/60 + this->_dec > 180)
                throw std::invalid_argument("Value error");
            break;
        case 'N':
        case 'S':
            if (this->_min/60 + this->_dec > 90)
                throw std::invalid_argument("Value error");
            break;
        default:
            throw std::invalid_argument("Value error orientaion");
    }
}

void angle::getValues(int& dec, float& min, char& orientaion) const{
    dec        = this->_dec;
    min        = this->_min;
    orientaion = this->_orientaion;
}

int angle::answerData() {
    int result = 0;
    std::cin >> this->_dec >> this->_min >> this->_orientaion;

    if (this->_min < 0 || this->_dec < 0)
        result = 1;

    switch (this->_orientaion) {
        case 'W':
        case 'E':
            if (this->_min/60 + this->_dec > 180)
                result = 1;
            break;
        case 'N':
        case 'S':
            if (this->_min/60 + this->_dec > 90)
                result = 1;
            break;
        default:
            result = 2;
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const angle& obj) {
    int dec;
    float min;
    char orientaion;
    obj.getValues( dec, min, orientaion );

    os << dec << "°" << min << "' " << orientaion;
    return os;
}


int main () {

    try {
        angle ang(10, 10.10, 'W');
        std::cout << ang << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    while(1) {
        std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";

        angle ang;
        if (ang.answerData() != 0) {
            std::cerr << "Ошибка при вводе!" << std::endl;
            continue;
        }
        std::cout << ang << std::endl;
    }

    return 0;
}
