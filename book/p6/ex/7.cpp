#include <iostream>
#include <ostream>

class angle {
    public:
        angle(): _dec(0), _min(0), _orientaion(' ')
        {}
        angle(int dec, int min, char orientaion): _dec(dec), _min(min), _orientaion(orientaion)
        {}

        void answerData();
        void getValues(int& dec, float& min, char& orientaion) const;

    private:
        int _dec;
        float _min;
        char _orientaion;
};

void angle::getValues(int& dec, float& min, char& orientaion) const{
    dec        = this->_dec;
    min        = this->_min;
    orientaion = this->_orientaion;
}

void angle::answerData() {
    std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";
    std::cin >> this->_dec >> this->_min >> this->_orientaion;
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
    angle ang(10, 10.10, 'W');

    std::cout << ang << std::endl;

    while(1) {
        ang.answerData();
        std::cout << ang << std::endl;
    }

    return 0;
}
