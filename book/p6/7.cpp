#include <iostream>
#include <ostream>
#include <stdexcept>

class angle {
    public:
        angle();
        angle(int dec, int min, char orientation);

        int answerData();
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
    const int totalDegrees = _min / 60 + _dec;

    if (this->_min < 0 || this->_dec < 0 ||
       (this->_orientation == 'W' || this->_orientation == 'E') && totalDegrees > 180 ||
       (this->_orientation == 'N' || this->_orientation == 'S') && totalDegrees > 90  ||
       (this->_orientation != 'W' && this->_orientation != 'E' && this->_orientation != 'N' && this->_orientation != 'S'))
        throw std::invalid_argument("Value error");
}

int angle::answerData() {
    std::cin >> this->_dec >> this->_min >> this->_orientation;

    const int totalDegrees = _min / 60 + _dec;

    if (this->_min < 0 || this->_dec < 0 ||
       (this->_orientation == 'W' || this->_orientation == 'E') && totalDegrees > 180 ||
       (this->_orientation == 'N' || this->_orientation == 'S') && totalDegrees > 90  ||
       (this->_orientation != 'W' && this->_orientation != 'E' && this->_orientation != 'N' && this->_orientation != 'S'))
        return 1;

    return 0;
}

std::ostream& operator<<(std::ostream& os, const angle& obj) {
    return os << obj._dec << "°" << obj._min << "' " << obj._orientation;
}


int main() {

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
