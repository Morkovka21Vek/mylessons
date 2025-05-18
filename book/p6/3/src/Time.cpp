#include "Time.hpp"
#include <iomanip>

Time::Time(): _hours(0), _min(0), _sec(0)
{}

Time::Time(unsigned int hours,
           unsigned int min,
           unsigned int sec
          ): _hours(hours), _min(min), _sec(sec)
{
    this->_min += this->_sec / 60;
    this->_sec %= 60;
    this->_hours += this->_min / 60;
    this->_min %= 60;

    //while(_sec >= 60) {
    //    _sec -= 60;
    //    _min++;
    //}
    //while(_min >= 60) {
    //    _min -= 60;
    //    _hours++;
    //}
}

void Time::getValues(
        unsigned int& hours,
        unsigned int& min,
        unsigned int& sec
        ) const {
    hours = _hours;
    min   = _min;
    sec   = _sec;
}

std::ostream& operator<<(std::ostream& os, const Time& obj) {
    unsigned int hours, min, sec;
    obj.getValues( hours, min, sec );

    os << std::setfill('0') << std::setw(2) << hours << ':' << std::setw(2) << min << ':' << std::setw(2) << sec;
    return os;
}

Time Time::operator+(const Time& other) const {
    unsigned int hours, min, sec;
    other.getValues( hours, min, sec );

    sec += this->_sec;
    min += this->_min;
    hours += this->_hours;

    min += this->_sec / 60;
    sec %= 60;
    hours += this->_min / 60;
    min %= 60;

    return Time(hours, min, sec);
}
