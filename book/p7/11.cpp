#include <iostream>
#include <string>
#include <iomanip>
#include <ostream>
#include <iomanip>

class dollar {
    public:
    	long double mstold(std::string);
		std::string ldtoms(long double sum);
		std::string ldtoms();
    private:
    	long double sum;
};

int main()
{
	dollar dl;

	while(true) {
        std::cout << "Введите сумму: " << std::flush;

        std::string str;
		std::getline(std::cin, str);

		long double ldsum = dl.mstold(str);

		std::cout << "Long double: " << std::fixed << std::setprecision(2) << ldsum << std::endl;

		std::string prettystr = dl.ldtoms();
		std::cout << "Pretty: " << prettystr << std::endl;
	}

	return 0;
}

long double dollar::mstold(std::string str)
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

std::string dollar::ldtoms()
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << sum;
	std::string str = oss.str();

	str.insert(str.begin(), '$');

	for (size_t i = 4; i < str.length() - 3; i += 4)
		str[i] = '\'';
	return str;
}

std::string dollar::ldtoms(long double sum)
{
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << sum;
	std::string str = oss.str();

	str.insert(str.begin(), '$');

	for (size_t i = 4; i < str.length() - 3; i += 4)
		str[i] = '\'';
	return str;
}
