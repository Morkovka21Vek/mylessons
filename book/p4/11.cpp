#include <iostream>

struct Time {
    int hours;
    int minutes;
    int seconds;
};

int main() {

    char tempChar;
    unsigned int timeSec;
    Time time1;
    Time time2;
    Time timeOut;

    std::cout << "Введите первое слагаемое в формате: hh:mm:ss" << std::endl
              << ">>> ";
    std::cin >> time1.hours >> tempChar >> time1.minutes >> tempChar >>
        time1.seconds;

    std::cout << "Введите второе слагаемое в формате: hh:mm:ss" << std::endl
              << ">>> ";
    std::cin >> time2.hours >> tempChar >> time2.minutes >> tempChar >>
        time2.seconds;

    timeSec = (time1.hours * 3600 + time1.minutes * 60 + time1.seconds) +
              (time2.hours * 3600 + time2.minutes * 60 + time2.seconds);

    timeOut.hours = static_cast<int>(timeSec / 3600);
    timeOut.minutes = static_cast<int>((timeSec - timeOut.hours * 3600) / 60);
    timeOut.seconds = timeSec - timeOut.hours * 3600 - timeOut.minutes * 60;

    std::cout << "Сумма равна " << timeOut.hours << ':' << timeOut.minutes
              << ':' << timeOut.seconds << std::endl;

    return 0;
}
