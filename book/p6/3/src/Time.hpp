#pragma once

#include <ostream>

class Time {
    public:
        Time();
        Time(unsigned int hours, 
             unsigned int min, 
             unsigned int sec
            );

        void getValues(
            unsigned int& hours, 
            unsigned int& min, 
            unsigned int& sec
            ) const;

        friend Time operator+(const Time&, const Time&);
        friend std::ostream& operator<<(std::ostream&, const Time&);

    private:
        unsigned int _hours;
        unsigned int _min;
        unsigned int _sec;
};
