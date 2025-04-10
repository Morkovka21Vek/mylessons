#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <sstream>

class date {
    public:
        date();
        date(int, int, int);
        date(std::string);
        void getValues(int& month, int& day, int& year) const;
        int parseDate(std::string str, date&, char sep='/');

    private:
        bool checkDate(std::vector<int>);
        std::vector<std::string> splitDate(std::string, char sep='/');

        int _month, _day, _year;
};

date::date(): _month(0), _day(0), _year(0)
{}

date::date(int month, int day, int year): _month(month), _day(day), _year(year)
{}

std::vector<std::string> date::splitDate(std::string str, char sep) {
    std::vector<std::string> result;

    std::stringstream ss(str);
    std::string temp;

    while(getline(ss, temp, sep))
        result.push_back(temp);
    //int pos = 0;
    //while ((pos = str.find(sep, pos)) != std::string::npos) {
    //    int lpos = str.find(sep, pos+1);
    //    int size = (lpos == std::string::npos) ? str.size()-pos : lpos-pos;
    //    result.push_back(str.substr(pos, size));
    //    if (pos+1 >= str.size())
    //        break;
    //    else
    //        pos++;
    //}
    return result;
}

bool date::checkDate(std::vector<int> input) {
    int result = -1;
    int day, month, year;

    if (input.size() != 3) {
        result = 1;
        goto ERROR;
    }

    day   = input[0];
    month = input[1];
    year  = input[2];

    if (year < 0 || month < 0 || month >= 12 || day < 0) {
        result = 2;
        goto ERROR;
    }

    switch (month) {
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            if (day > 31) {
                result = 3;
                goto ERROR;
            }
        case 3:
        case 5:
        case 8:
        case 10:
            if (day > 30) {
                result = 3;
                goto ERROR;
            }
        case 1:
            if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0)) {
                if (day > 29) {
                    result = 3;
                    goto ERROR;
                }
            } else {
                if (day > 28) {
                    result = 3;
                    goto ERROR;
                }
            }
    }

    result = 0;

ERROR:
    return result;
}

int date::parseDate(std::string str, date& dt, char sep) {
    std::vector<int> parse_int;
    std::vector<std::string> parse_str = splitDate(str, sep);

    for(int i = 0; i < parse_str.size(); i++) {
        parse_int.push_back(atoi(parse_str[i].c_str()));
    }

    int result = checkDate(parse_int);
    if (result == 0)
        dt = date(parse_int[1], parse_int[0], parse_int[2]);

    return result;

}

date::date(std::string str)
{
    if (parseDate(str, *this) != 0) {
        exit(1);
    }
}

void date::getValues(int& month, int& day, int& year) const{
    month = this->_month;
    day   = this->_day;
    year  = this->_year;
}

std::ostream& operator<<(std::ostream& os, const date& obj) {
    int month, day, year;
    obj.getValues( month, day, year );

    os << day << '/' << month << '/' << year;
    return os;
}

int main () {
    std::string str;
    std::cout << "Введите дату в формате dd/mm/yy:\n>> " << std::flush;
    std::cin >> str;

    date dt(str);

    std::cout << dt << std::endl;

    return 0;
}
