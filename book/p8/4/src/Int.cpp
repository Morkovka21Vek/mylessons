#include "Int.hpp"
#include <limits>

#define NOT_USED(var) static_cast<void>(var);

Int::Int(long double val):_num(val) {checkRange(val);}
Int::Int(int val):_num(val) {}

Int::Int() : _num(0) {}

std::strong_ordering Int::operator<=>(int val) const { return _num <=> val; }

Int &Int::operator=(int val) {
    _num = val;
    return *this;
}

Int operator+(const Int &obj1, int val) { return Int(obj1.checkRange(static_cast<long double>(obj1._num) + val)); }
Int operator+(int val, const Int &obj2) { return Int(obj2.checkRange(static_cast<long double>(obj2._num) + val)); }
Int operator+(const Int &obj1, const Int &obj2) {
    return Int(obj1.checkRange(static_cast<long double>(obj1._num) + obj2._num));
}

Int operator-(const Int &obj1, int val) { return Int(obj1.checkRange(static_cast<long double>(obj1._num) - val)); }
Int operator-(int val, const Int &obj2) { return Int(obj2.checkRange(static_cast<long double>(obj2._num) - val)); }
Int operator-(const Int &obj1, const Int &obj2) {
    return Int(obj1.checkRange(static_cast<long double>(obj1._num) - obj2._num));
}

Int &operator+=(Int &obj1, int val) {
    obj1._num += val;

    obj1.checkRange(obj1._num);

    return obj1;
}
Int &operator+=(Int &obj1, const Int &obj2) {
    obj1._num += obj2._num;

    obj1.checkRange(obj1._num);

    return obj1;
}

Int &operator-=(Int &obj1, int val) {
    obj1._num -= val;

    obj1.checkRange(obj1._num);

    return obj1;
}
Int &operator-=(Int &obj1, const Int &obj2) {
    obj1._num -= obj2._num;

    obj1.checkRange(obj1._num);

    return obj1;
}

bool operator>(int l, const Int &other) { return l > other._num; }
bool operator<(int l, const Int &other) { return l < other._num; }

bool operator>=(int l, const Int &other) { return l >= other._num; }
bool operator<=(int l, const Int &other) { return l <= other._num; }

std::ostream &operator<<(std::ostream &os, const Int &obj) {
    return os << obj._num;
}

int Int::checkRange(long double val) const {
    if (val > std::numeric_limits<int>::max() || val < std::numeric_limits<int>::min())
        throw std::out_of_range("Value exceeds int max limit!");
    return static_cast<int>(val);
}
