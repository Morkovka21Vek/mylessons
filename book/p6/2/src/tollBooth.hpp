#pragma once

#include <ostream>

class tollBooth {
    public:
        tollBooth() = default;

        void payingCar();
        void nopayCar();

        void display_get(std::ostream&) const;

    private:
        unsigned int _cars = 0;
        double _money = 0;
};

std::ostream& operator<<(std::ostream&, const tollBooth&);
