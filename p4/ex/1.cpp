#include <iostream>

struct phone {
	int cityCode;
	int stationCode;
	int abonentCode;
};

int main() {
	phone phone1, phone2;
	phone1 = {212, 767, 8900};

	std::cout << "Введите код города, номер станции и номер абонента через пробелы:" << std::endl << ">>> ";
	std::cin >> phone2.cityCode >> phone2.stationCode >> phone2.abonentCode;

	std::cout << "Первый телефон: (" << phone1.cityCode << ") " << phone1.stationCode << '-' << phone1.abonentCode << std::endl;
	std::cout << "Второй телефон: (" << phone2.cityCode << ") " << phone2.stationCode << '-' << phone2.abonentCode << std::endl;

	return 0;
}
