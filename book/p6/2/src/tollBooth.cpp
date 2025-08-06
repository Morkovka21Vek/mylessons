#include "tollBooth.hpp"

void tollBooth::payingCar() {
    this->_cars++;
    this->_money += 0.50;
}

void tollBooth::nopayCar() {
    this->_cars++;
}

std::ostream &operator<<(std::ostream &os, const tollBooth &obj) {
    os << "Cars: " << obj._cars << "\tMoney: " << obj._money << '$';
    return os;
}
