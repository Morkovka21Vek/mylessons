#include <iostream>
#include <cstdlib>

struct fraction {
  int a;
  int b;
};

int main() {
    int common_divi; // Переменная common_divi нужна для нахождения целого общего делителя у дроби
    fraction a, b, out;
    char dummychar, op, contin;

    std::cout << "Данная программа производит операции(+-*/) обычные дроби.\nДроби необходимо вводить в формате: \"x/y\"." << std::endl;
	
		do
		{
			std::cout << "Введите 1-ю дробь, опреранд и 2-ю дробь: \n>>> ";
	    std::cin >> a.a >> dummychar >> a.b >> op >> b.a >> dummychar >> b.b;

			switch (op){
				case '+':
					out.a = a.a * b.b + a.b * b.a;
    			out.b = a.b * b.b;
					break;

				case '-':
					out.a = a.a * b.b - a.b * b.a;
					out.b = a.b * b.b;
					break;

				case '*':
					out.a = a.a * b.a;
					out.b = a.b * b.b;
					break;

				case '/':
					out.a = a.a * b.b;
					out.b = a.b * b.a;
					break;

				default:
					std::cout << "Введён неправильный операнд!" << std::endl;
					std::exit(0);
					break;
			}
    

			int minNum, j;
			do {
				if (out.a == 0) {
					out.b = 0;
					break;
				}
				minNum = (out.a < out.b) ? out.a : out.b;
				for	(j = minNum; j > 0; j--) {
					if (!(out.a % j) && !(out.b % j)) {
						out.a /= j;
						out.b /= j;
						break;
					}
				}
			} while (j != 1);

			switch (op) {
				case '+':	
  	  		std::cout << "Сумма равна: >> " << out.a << "/" << out.b << std::endl;
					break;
				case '-':	
    			std::cout << "Разность равна: >> " << out.a << "/" << out.b << std::endl;
					break;
				case '*':	
    			std::cout << "Произведение равно: >> " << out.a << "/" << out.b << std::endl;
					break;			
				case '/':	
	    		std::cout << "Частное равно: >> " << out.a << "/" << out.b << std::endl;
					break;
			}
			
			std::cout << "Ешё раз? (Y/n): ";
			std::cin >> contin;
		} while (contin != 'n');

    return 0;
}
