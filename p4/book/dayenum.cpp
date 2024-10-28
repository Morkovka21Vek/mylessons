#include <iostream>

enum days_of_week {Mon, Tue, Wed, Thu, Fri, Sat, Sun};

int main() {
	days_of_week day1, day2;

	day1 = Mon;
	day2 = Thu;

	int diff = day2 - day1;
	diff = (diff > 0) ? diff : -diff;

	std::cout << "diff = " << diff << std::endl;
	if (day1 < day2)
		std::cout << "day1 < day2" << std::endl;
	else if (day1 > day2)
		std::cout << "day1 > day2" << std::endl;
	else if (day1 == day2)
		std::cout << "day1 = day2" << std::endl;
	else
		std::cout << "Чел, я незнаю как ты получит это сообщение, но мне кажется ты жульничал" << std::endl;

	return 0;
}
