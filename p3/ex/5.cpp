/* Условие:
 *
 * При помощи цикла for изобразите на экране пирамиду из символов 'X'. 
 * Верхняя часть пирамиды должна выглядеть следующим образом:

        х
      ххх
    ххххх 
  ххххххх 
ххххххххх

* Вся пирамида должна быть высотой не 5 линий, как изображено здесь, а 20 линий. 
* Одним из способов ее построения может служить использование двух вложенных циклов, из которых внутренний будет заниматься печатанием символов 'X' и пробелов, а другой осуществлять переход на одну строку вниз.
*/#include <iostream>
#include <iomanip>

int main() {
	const int count = 20;


	std::cout << "Выводим электронный вариант с помощью setw():" << std::endl << std::endl;
	for (int i = 1; i <= count * 2 - 1; i += 2)
		std::cout << std::left << std::setfill(' ') << std::setw(count*2-1 - i) << "" << std::setfill('X') << std::setw(i) << "" << std::endl;


	std::cout << std::endl << std::endl << "Выводим электронный вариант с помощью for:" << std::endl << std::endl;
	for (int i = 1; i <= count * 2 - 1; i += 2){

		for (int a = 0; a < count * 2 - 1; a++)
			if (a < (count * 2 - 1 - i))
				std::cout << ' ';
			else
				std::cout << 'X';

		std::cout << std::endl;
	}

		
	std::cout << std::endl << std::endl << "Выводим оригинальный вариант:" << std::endl << std::endl;
	for (int i = 1; i <= count; i++){

		for (int a = 0; a < count + i - 1; a++)
			if (a < (count - i))
				std::cout << ' ';
			else
				std::cout << 'X';

		std::cout << std::endl;
	}

	return 0;
}
