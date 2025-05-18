#include "tollBooth.hpp"

void tollBooth::payingCar() {
    this->_cars++;
    this->_money += 0.50;
}

void tollBooth::nopayCar() {
    this->_cars++;
}

void tollBooth::display_get(std::ostream& os) const {
    os << "Cars: " << this->_cars << "\tMoney: " << this->_money << '$';
}

std::ostream& operator<<(std::ostream& os, const tollBooth& obj) {
    obj.display_get(os);
    return os;
}
