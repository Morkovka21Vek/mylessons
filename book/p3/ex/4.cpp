/* Условие
 * Создайте эквивалент калькулятора, выполняющего четыре основных арифметических операции.
 * Программа должна запрашивать ввод пользователем первого операнда, знака операции и второго операнда. 
 * Для хранения операндов следует использовать переменные вещественного типа. 
 * Выбрать операцию можно при помощи оператора switch. 
 * В конце программа долж- на отображать результат на экране. 
 * Результат работы программы с пользователем может выглядеть следующим образом:
Введите первый операнд, операцию и второй операнд: 10 / 3
Результат равен 3.333333
Выполнить еще одну операцию (y/n)? y
Введите первый операнд, операцию и второй операнд: 12 + 100
Результат равен 112
Выполнить еще одну операцию (y/n)? n
*/
#include <iostream>

int main() {

	double a, b;
	char op;
	char again;

	do {
		std::cout << "Введите 1 операнд, операцию(+-*/) и 2 операнд через пробелы: \n>>> ";
		std::cin >> a >> op >> b;
	
		std::cout << a << ' ' << op << ' ' << b << " = ";

		switch (op) {
			case '+':
				std::cout << a + b;
				break;
			case '-':
				std::cout << a - b;
				break;
			case '*':
				std::cout << a * b;
				break;
			case '/':
				std::cout << a / b;
				break;
		}
		std::cout << std::endl << "Ещё раз? (Y/n): ";
		std::cin >> again;
	} while (again != 'n');

	return 0;
}

/*
using namespace std; 
int main() {
	double n1, n2, ans;
	char oper, ch;
	do {
		cout << "\nВведите первый операнд, операцию, второй операнд:";
		cin >> n1 >> oper >> n2;
		switch(oper)
		{
			case '+':ans = n1 + n2;break;
			case '-':ans = n1 - n2;break;
			case '*':ans = n1 * n2;break;
			case '/':ans = n1 / n2;break;
			default:ans = 0;
		}
		cout << "Ответ =" << ans;
		cout << "\nПродолжать (Введите 'y' или 'n')?";
		cin >> ch;
		} while(ch != 'n');
	return 0;
}*/