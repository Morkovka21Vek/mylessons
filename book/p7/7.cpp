#include <iomanip>
#include <iostream>
#include <string>

class dollar {
  public:
    dollar();
    dollar(std::string);
    long double mstold(std::string);
    friend std::ostream &operator<<(std::ostream &os, const dollar &obj);

  private:
    long double sum;
};

dollar::dollar(std::string str) { this->mstold(str); }

std::ostream &operator<<(std::ostream &os, const dollar &obj) {
    os << obj.sum;
    return os;
}

int main() {
    while (true) {
        std::cout << "Введите сумму: " << std::flush;

        std::string str;
        std::getline(std::cin, str);

        dollar dl = str;

        std::cout << "Long double: " << std::fixed << std::setprecision(2) << dl
                  << std::endl;
    }

    return 0;
}

long double dollar::mstold(std::string str) {
    for (size_t i = 0; i < str.length();) {
        char ch = str[i];
        if ((ch < '0' || ch > '9') &&
            ch != '.') { // ЭХХХХХ сюда бы регулярное выражение, но regex качать
                         // лень
            str.erase(i, 1);
        } else {
            i++;
        }
    }

    this->sum = std::stold(str);
    return this->sum;
}
