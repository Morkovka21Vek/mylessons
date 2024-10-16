/* Условие задачи:
 * Создайте калькулятор, выполняющий действия над денежными суммами, выраженными в фунтах, шиллингах и пенсах (см. упражнения 10 и 12 главы 2). 
 * Калькулятор должен складывать и вычитать вводимые значения, а также производить умножение денежной суммы на вещественное число (операция умножения двух денежных сумм не имеет смысла, поскольку квадратных денежных единиц не существует. 
 * Деление одной денежной суммы на другую мы тоже не будем рассматривать). 
 * Организация взаимодействия с калькулятором описана в упражнении 4 этой главы.
*/
#include <iostream>

int main() {

	int f1, s1, p1, f2, s2, p2, out_f, out_s, out_p, factor; 
	char ch, cont, op;

	do
	{
		std::cout << "Введите операнд(+-*): ";
		std::cin >> op;

		if (op == '+' || op == '-') 
		{
			std::cout << "Введите первую сумму: £";
			std::cin >> f1 >> ch >> s1 >> ch >> p1;
	
			std::cout << "Введите вторую сумму: £";
			std::cin >> f2 >> ch >> s2 >> ch >> p2;
		}
		
		switch (op) {
			case '+':
				out_p = (p1 + p2) % 12;
				out_s = static_cast<int>((p1 + p2) / 12);

				out_f = static_cast<int>((out_s + s1 + s2) / 20);
				out_s = (out_s + s1 + s2) % 20;

				out_f += f1 + f2;
				
				std::cout << "Сумма равна: £" << out_f << '.' << out_s << '.' << out_p << std::endl;
				break;

			case '-':
				out_p = (p1 - p2) % 12;
				if (out_p < 0) {
					out_s = static_cast<int>((p1 - p2) / 12) - 1;
					out_p = (out_s * -12) + out_p;
				} else {
					out_s = static_cast<int>((p1 - p2) / 12);
				}

				out_f = static_cast<int>((s1 - s2 + out_s) / 20);
				out_s = (s1 - s2 + out_s) % 20;
				if (out_s < 0) {
					out_f--;
					out_s = (out_f * -20) + out_s;
				}

				out_f += f1 - f2;

				std::cout << "Разность равна: £" << out_f << '.' << out_s << '.' << out_p << std::endl;
				break;

			case '*':
				std::cout << "Введите сумму: £";
				std::cin >> f1 >> ch >> s1 >> ch >> p1;
		
				std::cout << "Введите вещественное число(множитель): ";
				std::cin >> factor;

				out_p = (p1 * factor) % 12;
				out_s = static_cast<int>((p1 * factor) / 12);

				out_f = static_cast<int>((out_s * s1 * factor) / 20);
				out_s = (out_s + s1 * factor) % 20;

				out_f += f1 * factor;

				std::cout << "Произведение равно: £" << out_f << '.' << out_s << '.' << out_p << std::endl;
				break;
			default:
				std::cout << "Неверный операнд!" << std::endl;
				continue;
		}

		std::cout << "Продолжить? (Y/n): ";
		std::cin >> cont;

	} while (cont != 'n');

	return 0;
}
