#pragma once

#include <ostream>

class tollBooth {
  public:
    tollBooth() = default;

    void payingCar();
    void nopayCar();

    friend std::ostream &operator<<(std::ostream &, const tollBooth &);

  private:
    unsigned int _cars = 0;
    double _money = 0;
};
