#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

class bMoney {
  public:
    bMoney();
    explicit bMoney(long double);
    bMoney(const std::string &);
    long double mstold(std::string);
    std::string ldtoms(long double sum) const;
    std::string ldtoms() const;
    explicit operator long double();
    bMoney operator+(const bMoney &);
    bMoney operator-(const bMoney &);
    bMoney operator*(long double);
    double operator/(const bMoney &);
    bMoney operator/(long double);

  private:
    long double sum;
    friend std::ostream &operator<<(std::ostream &os, const bMoney &obj);
    friend bMoney operator*(long double, const bMoney&);
};

bMoney::bMoney(long double sum) : sum(sum) {}

bMoney bMoney::operator+(const bMoney &obj) {
    return bMoney(this->sum + obj.sum);
}

bMoney bMoney::operator-(const bMoney &obj) {
  return bMoney(this->sum - obj.sum);
}
bMoney bMoney::operator*(long double mul) {
  return bMoney(this->sum * mul);
}
double bMoney::operator/(const bMoney &obj) {
  return this->sum / obj.sum;
}
bMoney bMoney::operator/(long double div) {
  return bMoney(this->sum / div);
}
bMoney operator*(long double mul, const bMoney& obj) {
  return bMoney(obj.sum * mul);
}

bMoney::bMoney(const std::string &str) { this->mstold(str); }

std::ostream &operator<<(std::ostream &os, const bMoney &obj) {
    os << obj.ldtoms();
    return os;
}

bMoney::operator long double() { return sum; }

int main() {
  std::cout << "Для выхода нажмите Enter" << std::endl;
  while(true) {
    std::string str;

    std::cout << "Введите сумму 1: " << std::flush;

    std::getline(std::cin, str);
    if(str.length() == 0)
      break;
    bMoney bm1(str);

    std::cout << "Введите сумму 2: " << std::flush;

    std::getline(std::cin, str);
    if(str.length() == 0)
      break;
    bMoney bm2(str);

    std::cout << bm1 << " + " << bm2 << " = " << bm1 + bm2 << std::endl;
    std::cout << bm1 << " - " << bm2 << " = " << bm1 - bm2 << std::endl;
    std::cout << bm1 << " / " << bm2 << " = " << bm1 / bm2 << std::endl;

    std::cout << "Введите число: " << std::flush;
    long double var;
    std::cin >> var;
    std::cin.ignore();

    std::cout << bm1 << " * " << var << " = " << bm1 * var << std::endl;
    std::cout << var << " * " << bm2 << " = " << var * bm2 << std::endl;
    std::cout << bm1 << " / " << var << " = " << bm1 / var << std::endl;
  }

    return 0;
}

long double bMoney::mstold(std::string str) {
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

std::string bMoney::ldtoms() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << sum;
    std::string str = oss.str();

    str.insert(str.begin(), '$');

    for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos;
         i += 4, dot_pos++)
        str.insert(i, 1, '\'');
    return str;
}

std::string bMoney::ldtoms(long double sum) const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << sum;
    std::string str = oss.str();

    str.insert(str.begin(), '$');

    for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos;
         i += 4, dot_pos++)
        str.insert(i, 1, '\'');
    return str;
}
