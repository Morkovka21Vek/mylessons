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
        int parseDate(const std::string& str, date&, char sep='/') const;

        friend std::ostream& operator<<(std::ostream& os, const date& obj);

    private:
        int getDaysCount(int month, int year) const;
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

int date::getDaysCount(int month, int year) const {
    int days = 0;
    if (month == 1) {
        if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
            days = 29;
        } else {
            days = 28;
        }
    }
    else if (month == 3 ||
             month == 5 ||
             month == 8 ||
             month == 10)

        days = 30;
     else
        days = 31;

     return days;
}

bool date::checkDate(std::vector<int> input) const {
    int day;
    int month;
    int year;
    if (input.size() != 3)
        goto ERROR;

    day = input[0];
    month = input[1];
    year = input[2];

    if (year < 0 || month < 0 || month > 11 || day < 0)
        goto ERROR;

    if (day > getDaysCount(month, year))
        goto ERROR;

    return true;
ERROR:
    return false;
}

int date::parseDate(const std::string& str, date& dt, char sep) const {
    int result = 0;

    std::vector<int> parse_int;
    std::vector<std::string> parse_str = splitDate(str, sep);

    for (const auto& i : parse_str) {
        int val = 0;
        try {
            val = std::stoi(i);
        } catch(std::exception &e) {
            result = 1;
        }
        parse_int.push_back(val);
    }

    result = (!checkDate(parse_int) || result) ? 1 : 0;
    if (!result)
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
    return os << obj._day << '/' << obj._month << '/' << obj._year;
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
    catch(std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
