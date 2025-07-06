#include <iostream>
#include <string>
#include <iomanip>
#include <ostream>
#include <iomanip>

class bMoney {
    public:
		bMoney();
		bMoney(long double);
		bMoney(std::string);
    	long double mstold(std::string);
		std::string ldtoms(long double sum) const;
		std::string ldtoms() const;
		friend std::ostream &operator<<(std::ostream &os, const bMoney &obj);
		operator long double();
		bMoney operator+(bMoney&);
    private:
    	long double sum;
};

bMoney::bMoney(long double sum):sum(sum) {}

bMoney bMoney::operator+(bMoney& obj) {
	return bMoney(this->sum + obj.sum);
}

bMoney::bMoney(std::string str) {
	this->mstold(str);
}

std::ostream &operator<<(std::ostream &os, const bMoney &obj) {
	os << obj.ldtoms();
    return os;
}

bMoney::operator long double() {
	return sum;
}

int main()
{
    std::string str;

    std::cout << "Введите сумму 1: " << std::flush;

	std::getline(std::cin, str);
	bMoney bm1(str);

    std::cout << "Введите сумму 2: " << std::flush;

	std::getline(std::cin, str);
	bMoney bm2(str);

	std::cout << "Сумма: " << bm1 + bm2 << std::endl;

	return 0;
}

long double bMoney::mstold(std::string str)
{
	for (size_t i = 0; i < str.length();) {
		char ch = str[i];
		if ((ch < '0' || ch > '9') && ch != '.') {
			str.erase(i, 1);
		}
		else {
			i++;
		}
	}

	this->sum = std::stold(str);
	return this->sum;
}

std::string bMoney::ldtoms() const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << sum;
	std::string str = oss.str();

	str.insert(str.begin(), '$');

	for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos; i += 4, dot_pos++)
		str.insert(i, 1, '\'');
	return str;
}

std::string bMoney::ldtoms(long double sum) const
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << sum;
	std::string str = oss.str();

	str.insert(str.begin(), '$');

	for (size_t dot_pos = str.length() - 3, i = 4; i < dot_pos; i += 4, dot_pos++)
		str.insert(i, 1, '\'');
	return str;
}
