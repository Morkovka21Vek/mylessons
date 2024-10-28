#include <iostream>

const int clubs = 0;
const int diamonds = 1;
const int hearts = 2;
const int spades = 3;
const int jack = 11;
const int queen = 12;
const int king = 13;
const int ace = 14;

struct card {
	int number;
	int suit;
};

int main() {
	card temp, chosen, prize;
	int position;

	card card1 = {7, clubs};
	std::cout << "Card1: " << card1.number << '\t' << card1.suit << std::endl;

	card card2 = {jack, hearts};
	std::cout << "Card2: " << card2.number << '\t' << card2.suit << std::endl;

	card card3 = {ace, spades};
	std::cout << "Card3: " << card3.number << '\t' << card3.suit << std::endl;
	
	std::cout << std::endl;

	prize = card3;

	std::cout << "1 <-> 3" << std::endl;
	temp = card3; card3 = card1; card1 = temp;

	std::cout << "2 <-> 3" << std::endl;
	temp = card3; card3 = card2; card2 = temp;

	std::cout << "1 <-> 2" << std::endl;
	temp = card2; card2 = card1; card1 = temp;

	std::cout << "Card3 on position(1, 2, 3)"; 
	std::cin >> position;

	switch (position) 
	{
		case 1: chosen = card1; break;
		case 2: chosen = card2; break;
		case 3: chosen = card3; break;
	}

	if (chosen.number == prize.number && chosen.suit == prize.suit)
		std::cout << "Победил" << std::endl;
	else
		std::cout << "Проиграл" << std::endl;
	
	return 0;
}
