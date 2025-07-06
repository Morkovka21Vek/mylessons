#include "Time.hpp"
#include <format>

Time::Time() : _hours(0), _min(0), _sec(0) {}

Time::Time(unsigned int hours, unsigned int min, unsigned int sec)
    : _hours(hours), _min(min), _sec(sec) { normalize(); }

std::ostream &operator<<(std::ostream &os, const Time &obj) {
    return os << std::format("{:02}:{:02}:{:02}", obj._hours, obj._min,
                             obj._sec);
}

Time operator+(const Time &obj1, const Time &obj2) {
    unsigned int hours = obj1._hours + obj2._hours;
    unsigned int min = obj1._min + obj2._min;
    unsigned int sec = obj1._sec + obj2._sec;

    return Time(hours, min, sec);
}

Time operator*(const Time &obj1, float mul) {
    return Time(obj1._hours*mul, obj1._min*mul, obj1._sec*mul);
}

Time operator-(const Time &obj1, const Time &obj2) {
    unsigned long secs1 = obj1._hours*3600+obj1._min*60+obj1._sec;
    unsigned long secs2 = obj2._hours*3600+obj2._min*60+obj2._sec;

    unsigned long secs_sub = secs1 - secs2;

    int hours = secs_sub / 3600;
    int rem = secs_sub % 3600;
    int min = rem / 60;
    int sec = rem % 60;

    return Time(hours, min, sec);
}

Time& Time::operator++() {
    this->_min++;
    normalize();
    return *this;
}
Time& Time::operator--() {
    this->_min--;
    normalize();
    return *this;
}
Time& Time::operator++(int) {
    ++this->_min;
    normalize();
    return *this;
}
Time& Time::operator--(int) {
    --this->_min;
    normalize();
    return *this;
}
void Time::normalize() {
    this->_min += this->_sec / 60;
    this->_sec %= 60;
    this->_hours += this->_min / 60;
    this->_min %= 60;
}
