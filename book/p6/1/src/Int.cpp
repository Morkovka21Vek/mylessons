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


Int& Int::operator+=(int val)
{
    _num += val;
    return *this;
}
Int& Int::operator+=(const Int& other)
{
    _num += other.getValue();
    return *this;
}

Int& Int::operator-=(int val)
{
    _num -= val;
    return *this;
}
Int& Int::operator-=(const Int& other)
{
    _num -= other.getValue();
    return *this;
}

Int Int::operator+(int val) const
{
    return Int(_num + val);
}

Int Int::operator+(const Int& other) const
{
    return Int(_num + other.getValue());
}

Int Int::operator-(int val) const
{
    return Int(_num - val);
}

Int Int::operator-(const Int& other) const
{
    return Int(_num - other.getValue());
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

bool Int::operator>=(const Int& other) const {
    return _num >= other._num;
}
bool Int::operator<=(const Int& other) const {
    return _num <= other._num;
}

bool operator>=(int l, const Int& other) {
    return l >= other.getValue();
}
bool operator<=(int l, const Int& other) {
    return l <= other.getValue();
}

int Int::getValue() const {
    return _num;
}

std::ostream& operator<<(std::ostream& os, const Int& obj) {
    os << obj.getValue();
    return os;
}
