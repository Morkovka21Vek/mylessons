#include <iostream>
#include <ostream>
#include <stdexcept>

class angle {
    public:
        angle();
        angle(int dec, int min, char orientation);

        int answerData();
        void getValues(int& dec, float& min, char& orientation) const;

        friend std::ostream& operator<<(std::ostream& os, const angle& obj);

    private:
        int _dec;
        float _min;
        char _orientation;
};

angle::angle(): _dec(0), _min(0), _orientation('W')
{}

angle::angle(int dec, int min, char orientation): _dec(dec), _min(min), _orientation(orientation)
{
    if (this->_min < 0 || this->_dec < 0)
        throw std::invalid_argument("Value error");

    if (this->_orientation == 'W' || this->_orientation == 'E') {
        if (this->_min/60 + this->_dec > 180)
            throw std::invalid_argument("Value error");
    } else if (this->_orientation == 'N' || this->_orientation == 'S') {
        if (this->_min/60 + this->_dec > 90)
            throw std::invalid_argument("Value error");
    } else
        throw std::invalid_argument("Value error orientation");
}

void angle::getValues(int& dec, float& min, char& orientation) const{
    dec        = this->_dec;
    min        = this->_min;
    orientation = this->_orientation;
}

int angle::answerData() {
    int result = 0;
    std::cin >> this->_dec >> this->_min >> this->_orientation;

    if (this->_min < 0 || this->_dec < 0)
        result = 1;

    if (this->_orientation == 'W' || this->_orientation == 'E') {
        if (this->_min/60 + this->_dec > 180)
            result = 1;
    } else if (this->_orientation == 'N' || this->_orientation == 'S') {
        if (this->_min/60 + this->_dec > 90)
            result = 1;
    } else
        result = 2;

    return result;
}

std::ostream& operator<<(std::ostream& os, const angle& obj) {
    return os << obj._dec << "°" << obj._min << "' " << obj._orientation;
}


int main () {

    try {
        angle ang(10, 10.10, 'W');
        std::cout << ang << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    while(true) {
        std::cout << "Введите координаты в формате: \"d m orientation\"\n>>> ";

        angle ang;
        if (ang.answerData() != 0) {
            std::cerr << "Ошибка при вводе!" << std::endl;
            continue;
        }
        std::cout << ang << std::endl;
    }
}
