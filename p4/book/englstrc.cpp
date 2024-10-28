#include <iostream>

struct Distance
{
	int feet;
	float inches;
};

int main() 
{
	Distance d1, d3;
	Distance d2 = {11, 6.25};

	std::cout << std::endl << "Введите число футов: >>> "; std::cin >> d1.feet;
	std::cout << "Введиет число дюймов: >>> ";						 std::cin >> d1.inches;

	d3.inches = d1.inches + d2.inches;
	d3.feet = 0;

	if (d3.inches >= 12) 
	{
		d3.inches -= 12;
		d3.feet ++;
	}

	d3.feet += d1.feet + d2.feet;

	std::cout << d1.feet << "\'-" << d1.inches << "\" + "
						<< d2.feet << "\'-" << d2.inches << "\" = "
						<< d3.feet << "\'-" << d3.inches << '\"' << std::endl;

	return 0;
}
