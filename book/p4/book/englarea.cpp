#include <iostream>

struct Distance {
	int feet;
	float inches;
};

struct Room {
	Distance length;
	Distance width;
};

int main() {
	Room dining;

	dining.length.feet = 13;
	dining.length.inches = 6.5F;
	dining.width.feet = 10;
	dining.width.inches = 0.0;

	float l = dining.length.feet + dining.length.inches/12;
	float w = dining.width.feet + dining.width.inches/12;

	std::cout << "S = " << l*w << " feet²" << std::endl;

	return 0;
}
