#include <iostream>
#include <ostream>

class ship {
    public:
        ship();
        int answerData();
        void getValues(int& num, int& dec, float& min, char& orientaion) const;

    private:
        static int _count;
        int _num;

        int _dec;
        float _min;
        char _orientaion;
};

int ship::_count = 1;

ship::ship() {
    _num = _count;
    _count++;
}

int ship::answerData() {
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

void ship::getValues(int& num, int& dec, float& min, char& orientaion) const{
    num        = this->_num;
    dec        = this->_dec;
    min        = this->_min;
    orientaion = this->_orientaion;
}

std::ostream& operator<<(std::ostream& os, const ship& obj) {
    int num;
    int dec;
    float min;
    char orientaion;
    obj.getValues( num, dec, min, orientaion );

    os << "Shup №" << num << ": " << dec << "°" << min << "' " << orientaion;
    return os;
}



int main () {
    ship sh1, sh2, sh3;

    std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";
    if (sh1.answerData() != 0)
        goto INPUT_ERROR;

    std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";
    if (sh2.answerData() != 0)
        goto INPUT_ERROR;

    std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";
    if (sh3.answerData() != 0)
        goto INPUT_ERROR;

    std::cout << sh1 << std::endl
              << sh2 << std::endl
              << sh3 << std::endl;

    return 0;

INPUT_ERROR:
    std::cerr << "Ошибка при вводе!" << std::endl;
    return 1;
}
