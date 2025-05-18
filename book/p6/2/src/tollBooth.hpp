#pragma once

#include <ostream>

class tollBooth {
    public:
        tollBooth();

        void payingCar();
        void nopayCar();

        void display_get(std::ostream&) const;

    private:
        unsigned int _cars;
        double _money;
};

std::ostream& operator<<(std::ostream&, const tollBooth&);
