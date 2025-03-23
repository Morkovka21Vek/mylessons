#include "Int.hpp"

#define NOT_USED(var) static_cast<void>(var);

Int::Int(int val):_num(val)
{}

Int::Int():_num(0)
{}

bool Int::operator==(int val) const {
    return _num == val;
}

bool Int::operator==(const Int& other) const {
    return _num == other._num;
}

bool Int::operator!=(const Int& other) const {
    return _num != other._num;
}

Int& Int::operator=(int val)
{
    _num = val;
    return *this;
}

bool Int::operator>(const Int& other) const {
    return _num > other._num;
}
bool Int::operator<(const Int& other) const {
    return _num < other._num;
}

bool operator>(int l, const Int& other) {
    return l > other.getValue();
}
bool operator<(int l, const Int& other) {
    return l < other.getValue();
}

int Int::getValue() const {
    return _num;
}
