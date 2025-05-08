#include <iostream>

struct Time {
    int hours;
    int minutes;
    int seconds;
};

int main() {

    char tempChar;
    Time time1;

    std::cout << "Введите время в формате: hh:mm:ss" << std::endl << ">>>";
    std::cin >> time1.hours >> tempChar >> time1.minutes >> tempChar >>
        time1.seconds;

    std::cout << "В секундах это: "
              << (time1.hours * 3600 + time1.minutes * 60 + time1.seconds)
              << std::endl;

    return 0;
}
