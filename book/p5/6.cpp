#include <iostream>

struct Time {
    int hours;
    int mins;
    int secs;
};

long time_to_secs(Time time) {
    return time.hours * 3600 + time.mins * 60 + time.secs;
}

Time secs_to_time(long secs) {
    Time time;

    time.mins = secs / 60;
    time.secs = secs % 60;
    time.hours = time.mins / 60;
    time.mins %= 60;

    return time;
}

int main() {

    Time time1;
    Time time2;
    Time timeOut;

    std::cout << "Введите первое слагаемое в формате: \"hh mm ss\": ";
    std::cin >> time1.hours >> time1.mins >> time1.secs;

    std::cout << "Введите второе слагаемое в формате: \"hh mm ss\": ";
    std::cin >> time2.hours >> time2.mins >> time2.secs;

    timeOut = secs_to_time(time_to_secs(time1) + time_to_secs(time2));
    std::cout << "Сумма равна " << timeOut.hours << ':' << timeOut.mins << ':'
              << timeOut.secs << std::endl;

    return 0;
}
