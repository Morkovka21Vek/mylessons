#include <iostream>
#include <ostream>

class counter {
    public:
        counter();
        friend std::ostream& operator<<(std::ostream& os, const counter& obj);

    private:
        int _num;
        static int _count;
};

int counter::_count = 1;

counter::counter() {
    _num = _count;
    _count++;
}

std::ostream& operator<<(std::ostream& os, const counter& obj) {
    return os << obj._num;
}

int main () {
    counter ct1;
    counter ct2;
    counter ct3;

    std::cout << "Мой номер: " << ct1 << std::endl
              << "Мой номер: " << ct2 << std::endl
              << "Мой номер: " << ct3 << std::endl;

    return 0;
}
