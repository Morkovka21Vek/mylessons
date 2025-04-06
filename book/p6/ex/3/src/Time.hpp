#pragma once

#include <ostream>

class Time {
    public:
        Time();
        Time(unsigned int hours, 
             unsigned int min, 
             unsigned int sec
            );

        Time operator+(const Time& other) const;

        void getValues(
            unsigned int& hours, 
            unsigned int& min, 
            unsigned int& sec
            ) const;

    private:
        unsigned int _hours;
        unsigned int _min;
        unsigned int _sec;
};

std::ostream& operator<<(std::ostream&, const Time&);
