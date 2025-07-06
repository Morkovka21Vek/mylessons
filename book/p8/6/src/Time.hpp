#pragma once

#include <ostream>

class Time {
  public:
    Time();
    Time(unsigned int hours, unsigned int min, unsigned int sec);

    Time& operator++();
    Time& operator--();
    Time& operator++(int);
    Time& operator--(int);

  private:
    friend Time operator+(const Time &, const Time &);
    friend Time operator-(const Time &, const Time &);
    friend Time operator*(const Time &, float);
    friend std::ostream &operator<<(std::ostream &, const Time &);

    void normalize();

    unsigned int _hours;
    unsigned int _min;
    unsigned int _sec;
};
