#include <iostream>

struct date {
    int day;
    int month;
    int year;
};

int main() {
    char slash;

    date date1;
    std::cout
        << "Введите дату в формате dd/mm/yyyy (левые нули можно отбросить)"
        << std::endl
        << ">>> ";
    std::cin >> date1.day >> slash >> date1.month >> slash >> date1.year;

    std::cout << date1.day << '/' << date1.month << '/' << date1.year
              << std::endl;

    return 0;
}
