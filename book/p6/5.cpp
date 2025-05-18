#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>

class date {
    public:
        date() = default;
        date(int, int, int);
        explicit date(const std::string&);
        void getValues(int& month, int& day, int& year) const;
        int parseDate(const std::string& str, date&, char sep='/');

    private:
        bool checkDate(std::vector<int>) const;
        std::vector<std::string> splitDate(const std::string&, char sep='/') const;

        int _month = 0;
        int _day = 0;
        int _year = 0;
};

date::date(int month, int day, int year): _month(month), _day(day), _year(year)
{}

std::vector<std::string> date::splitDate(const std::string& str, char sep) const {
    std::vector<std::string> result;

    std::stringstream ss(str);
    std::string temp;

    while(getline(ss, temp, sep))
        result.push_back(temp);
    return result;
}

bool date::checkDate(std::vector<int> input) const {
    int day;
    int month;
    int year;

    if (input.size() != 3)
        goto ERROR;

    day   = input[0];
    month = input[1];
    year  = input[2];

    if (year < 0 || month < 0 || month >= 12 || day < 0)
        goto ERROR;

    if (month == 1) {
        if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
            if (day > 29) {
                goto ERROR;
            }
        } else {
            if (day > 28) {
                goto ERROR;
            }
        }
    }

    else if (month == 3 ||
             month == 5 ||
             month == 8 ||
             month == 10) {

        if (day > 30)
            goto ERROR;
    } else {
        if (day > 31)
            goto ERROR;
    }

    return 0;
ERROR:
    return 1;
}

int date::parseDate(const std::string& str, date& dt, char sep) {
    std::vector<int> parse_int;
    std::vector<std::string> parse_str = splitDate(str, sep);

    for (auto i : parse_str) {
        parse_int.push_back(atoi(i.c_str()));
    }

    int result = checkDate(parse_int);
    if (result == 0)
        dt = date(parse_int[1], parse_int[0], parse_int[2]);

    return result;

}

date::date(const std::string& str)
{
    if (parseDate(str, *this) != 0) {
        throw std::invalid_argument("Date format error");
    }
}

void date::getValues(int& month, int& day, int& year) const{
    month = this->_month;
    day   = this->_day;
    year  = this->_year;
}

std::ostream& operator<<(std::ostream& os, const date& obj) {
    int month;
    int day;
    int year;
    obj.getValues( month, day, year );

    os << day << '/' << month << '/' << year;
    return os;
}

void runCalendar() {
    std::string str;
    std::cout << "Введите дату в формате dd/mm/yyyy:\n>> " << std::flush;
    std::cin >> str;

    date dt(str);

    std::cout << dt << std::endl;
}


int main() {
    try {
        runCalendar();
    }
    catch(std::exception e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
