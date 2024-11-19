#include <iostream>

struct part {
	int modelNumber;
	int partNumber;
	float cost;
};

int main() {
	part part1;
	part1.modelNumber = 6244;
	part1.partNumber = 373;
	part1.cost = 217.55F;
	
	std::cout << "Номер модели: " << part1.modelNumber << std::endl
						<< "Номер детали: " << part1.partNumber << std::endl
						<< "Цена: "	 							<< part1.cost << std::endl;
	return 0;
}
