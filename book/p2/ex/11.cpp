#include <iostream>
#include <iomanip>

using namespace std;
int main() {
    cout << left << setfill(' ') << setw(30) << "Фамилия" << setw(30) << "Имя" << setw(30) << "Адрес" << setw(30) << "Город" << endl
         << left << setfill('-') << setw(120) << '-' << endl
         << left << setfill(' ') << setw(30) << "Петров"    << right  << setw(30) << "Василий" << left << setw(30) << "Кленовая 16" << setw(30) << "Санкт-Петербург" << endl
         << left << setfill(' ') << setw(30) << "Иванов"    << setw(30) << "Сергей"  << setw(30) << "Осиновая 3" << setw(30) << "Находка" << endl
         << left << setfill(' ') << setw(30) << "Сидоров"   << setw(30) << "Иван"    << setw(30) << "Березовая 21" << setw(30) << "Калининград" << endl;
    return 0;
}
