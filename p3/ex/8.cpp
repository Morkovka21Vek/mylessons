/* Условие
 *
 * Напишите программу, которая циклически будет запрашивать ввод пользователем двух денежных сумм, выраженных в фунтах, шиллингах и пенсах (см. упражнения 10 и 12 главы 2). 
 * Программа должна складывать введенные суммы и выводить на экран результат, также выраженный в фунтах, шиллингах и пенсах. 
 * После каждой итерации программа должна спрашивать пользователя, желает ли он продолжать работу программы. 
 * При этом рекомендуется использовать цикл do. Естественной формой взаимодействия программы с пользователем была бы следующая:
Введите первую сумму £5 10 6 
Введите первую сумму £3 2 6 
Всего £8 13 0 
Продолжить(y/n) ?
 * Для того чтобы сложить две суммы, вам необходимо учесть заем одного шиллинга в том случае, если число пенсов окажется больше 11, и одного фунта, если число шиллингов окажется больше 19.
*/

#include <iostream>

int main() {

	int f1, s1, p1, f2, s2, p2, out_f, out_s, out_p; 
	char ch, cont;

	do
	{
		std::cout << "Введите первую сумму: £";
		std::cin >> f1 >> ch >> s1 >> ch >> p1;

		std::cout << "Введите вторую сумму: £";
		std::cin >> f2 >> ch >> s2 >> ch >> p2;
	
		out_p = (p1 + p2) % 12;
		out_s = static_cast<int>((p1 + p2) / 12);

		out_f = static_cast<int>((out_s + s1 + s2) / 20);
		out_s = (out_s + s1 + s2) % 20;

		out_f += f1 + f2;

		std::cout << "Сумма равна: £" << out_f << '.' << out_s << '.' << out_p << std::endl
							<< "Продолжить? (Y/n): ";
		std::cin >> cont;

	} while (cont != 'n');

	return 0;
}