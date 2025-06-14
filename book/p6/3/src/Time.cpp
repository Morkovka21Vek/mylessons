#include "Time.hpp"
#include <format>

Time::Time() : _hours(0), _min(0), _sec(0) {}

Time::Time(unsigned int hours, unsigned int min, unsigned int sec)
    : _hours(hours), _min(min), _sec(sec) {
    this->_min += this->_sec / 60;
    this->_sec %= 60;
    this->_hours += this->_min / 60;
    this->_min %= 60;
}

std::ostream &operator<<(std::ostream &os, const Time &obj) {
    return os << std::format("{:02}:{:02}:{:02}", obj._hours, obj._min,
                             obj._sec);
}

Time operator+(const Time &obj1, const Time &obj2) {
    unsigned int hours = obj1._hours + obj2._hours;
    unsigned int min = obj1._min + obj2._min;
    unsigned int sec = obj1._sec + obj2._sec;

    min += sec / 60;
    sec %= 60;
    hours += min / 60;
    min %= 60;

    return Time(hours, min, sec);
}
