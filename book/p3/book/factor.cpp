#include <iostream>

int main() {

	unsigned int num;
	unsigned long fact = 1;

	std::cout << "Для подсчёта факториала числа введите целое число:\n>>> ";
	std::cin >> num;
	
	if (num > 12) 
		std::cout << "Слишком большое число!\nРезудьтат неверный(но посмотреть его разрешаю)!\n(Макс. 12)" << std::endl;

	for (int j=num; j>0; j--)
		fact *= j;

	std::cout << "Факториал равен " << fact << std::endl;
	
	return 0;
}
