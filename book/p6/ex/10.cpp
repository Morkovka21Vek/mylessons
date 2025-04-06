#include <iostream>
#include <ostream>

class ship {
    public:
        ship();
        void answerData();
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

void ship::answerData() {
    std::cout << "Введите координаты в формате: \"d m orientaion\"\n>>> ";
    std::cin >> this->_dec >> this->_min >> this->_orientaion;
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

    sh1.answerData();
    sh2.answerData();
    sh3.answerData();
    std::cout << sh1 << std::endl
              << sh2 << std::endl
              << sh3 << std::endl;

    return 0;
}
