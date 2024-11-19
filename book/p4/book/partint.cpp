#include <iostream>

struct part {
	int modelNumber;
	int partNumber;
	float cost;
};

int main() {

	part part1 = {6244, 373, 217.55F};
	part part2;

	std::cout << "Модель " << part1.modelNumber << std::endl
						<< "Деталь " << part1.partNumber  << std::endl
						<< "Цена "   << part1.cost        << std::endl << std::endl;

	part2 = part1;

	std::cout << "Модель " << part2.modelNumber << std::endl
						<< "Деталь " << part2.partNumber  << std::endl
						<< "Цена "   << part2.cost        << std::endl;

	return 0;
}
