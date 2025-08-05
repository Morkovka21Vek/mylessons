#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

class dollar {
  public:
    dollar();
    dollar(const std::string &);
    long double mstold(std::string);
    std::string ldtoms(long double sum);
    std::string ldtoms();
    explicit operator long double();

  private:
    long double sum;
    friend std::ostream &operator<<(std::ostream &os, const dollar &obj);
};

dollar::dollar(const std::string &str) {
    this->mstold(str);
}

std::ostream &operator<<(std::ostream &os, dollar &obj) {
    os << obj.ldtoms();
    return os;
}

dollar::operator long double() {
    return sum;
}

int main() {
    while (true) {
        std::cout << "Введите сумму: " << std::flush;

        std::string str;
        std::getline(std::cin, str);

        dollar dl = str;

        std::cout << "Long double: " << std::fixed << std::setprecision(2)
                  << static_cast<long double>(dl) << std::endl;

        std::cout << "Pretty: " << dl << std::endl;
    }
}

long double dollar::mstold(std::string str) {
    for (size_t i = 0; i < str.length();) {
        char ch = str[i];
        if ((ch < '0' || ch > '9') && ch != '.') {
            str.erase(i, 1);
        } else {
            i++;
        }
    }

    this->sum = std::stold(str);
    return this->sum;
}

std::string dollar::ldtoms() {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << sum;
    std::string str = oss.str();

    str.insert(str.begin(), '$');

    for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos;
         i += 4, dot_pos++)
        str.insert(i, 1, '\'');
    return str;
}

std::string dollar::ldtoms(long double sum) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << sum;
    std::string str = oss.str();

    str.insert(str.begin(), '$');

    for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos;
         i += 4, dot_pos++)
        str.insert(i, 1, '\'');
    return str;
}
