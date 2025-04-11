#include <iostream>

struct Time {
  int hours;
  int mins;
  int secs;
};

void swap(Time& a, Time& b) {
    Time temp;

    temp = a;
    a = b;
    b = temp;
}

int main() {
    Time a = {1, 2, 3}, b = {3, 2, 1};
    std::cout << "a = {" << a.hours << ", " << a.mins << ", " << a.secs << "}; b = {" << b.hours << ", " << b.mins << ", " << b.secs << '}' << std::endl;

    std::cout << "Swapping..." << std::endl;
    swap(a, b);

    std::cout << "a = {" << a.hours << ", " << a.mins << ", " << a.secs << "}; b = {" << b.hours << ", " << b.mins << ", " << b.secs << '}' << std::endl;

    return 0;
}
