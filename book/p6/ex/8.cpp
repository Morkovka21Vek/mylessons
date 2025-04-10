#include <iostream>
#include <ostream>

class counter {
    public:
        counter();
        int getValue() const;

    private:
        int _num;
        static int _count;
};

int counter::_count = 1;

counter::counter() {
    _num = _count;
    _count++;
}

int counter::getValue() const{
    return this->_num;
}

std::ostream& operator<<(std::ostream& os, const counter& obj) {
    os << obj.getValue();
    return os;
}


int main () {
    counter ct1, ct2, ct3;

    std::cout << "Мой номер: " << ct1 << std::endl
              << "Мой номер: " << ct2 << std::endl
              << "Мой номер: " << ct3 << std::endl;

    return 0;
}
