#include <iostream>
#include <ostream>

class date {
    public:
        void getDate();
        void getValues(int& month, int& day, int& year) const;

    private:
        int _month, _day, _year;
};

void date::getValues(int& month, int& day, int& year) const{
    month = this->_month;
    day   = this->_day;
    year  = this->_year;
}

void date::getDate() {
    char blackhole;

    std::cout << "Введите дату в формате dd/mm/yy:\n>> " << std::flush;
    std::cin >> _day >> blackhole >> _month >> blackhole >> _year;
}

std::ostream& operator<<(std::ostream& os, const date& obj) {
    int month, day, year;
    obj.getValues( month, day, year );

    os << day << '/' << month << '/' << year;
    return os;
}


int main () {
    date dt;

    dt.getDate();
    std::cout << dt << std::endl;

    return 0;
}
