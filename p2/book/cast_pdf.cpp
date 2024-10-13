// cast.cpp
// работа со знаковыми и беззнаковыми переменными
#include <iostream>
using namespace std;
int main() {
	int intVar = 1500000000; // 1 500 000 000
	intVar = (intVar * 10) / 10; // слишком большой результат
	cout << "Значение intVar равно " << intVar << endl; // неверный результат
	intVar = 1500000000;
	intVar = (static_cast<double>(intVar) * 10) / 10; // приведение к типу double
	cout << "Значение intVar равно " << intVar << endl; // верный результат
	return 0;
}
