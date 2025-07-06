#include <iostream>
#include <string>
#include <iomanip>

class dollar {
    public:
    	long double mstold(std::string);
    private:
    	long double sum;
};

int main()
{
	dollar ms;

	while(true) {
        std::cout << "Введите сумму: " << std::flush;

        std::string str;
		std::getline(std::cin, str);

		long double ldsum = ms.mstold(str);

		std::cout << "Long double: " << std::fixed << std::setprecision(2) << ldsum << std::endl;
	}

	return 0;
}

long double dollar::mstold(std::string str)
{
	for (size_t i = 0; i < str.length();) {
		char ch = str[i];
		if ((ch < '0' || ch > '9') && ch != '.') { // ЭХХХХХ сюда бы регулярное выражение, но regex качать лень
			str.erase(i, 1);
		}
		else {
			i++;
		}
	}

	this->sum = std::stold(str);
	return this->sum;
}
