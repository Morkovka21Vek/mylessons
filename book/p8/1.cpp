#include <iostream>
#include <ostream>

class Distance {
  public:
    Distance();
    Distance(int feet, float inches);
    Distance operator-(Distance d);

  private:
    friend std::ostream &operator<<(std::ostream &os, const Distance &obj);
    friend std::istream &operator>>(std::istream &in, Distance &d);

    int feet;
    float inches;
};

Distance::Distance() : feet(0), inches(0) {}
Distance::Distance(int feet, float inches) : feet(feet), inches(inches) {}

std::ostream &operator<<(std::ostream &os, const Distance &obj) {
    return os << obj.feet << "\'-" << obj.inches << '\"';
}

std::istream &operator>>(std::istream &in, Distance &d) {
    in >> d.feet >> d.inches;
    return in;
}

Distance Distance::operator-(Distance d) {
	float i = inches - d.inches;
	int adjust = static_cast<int>(i / 12.0);
	i -= adjust * 12.0;
	int f = feet - d.feet + adjust;
	return Distance(f, i);
}

int main() {

    std::cout << "Вводите расстояния в формате \"feet inches\"."
              << std::endl;

	Distance d1;
    std::cout << ">> " << std::flush;
	std::cin >> d1;

	Distance d2;
    std::cout << ">> " << std::flush;
	std::cin >> d2;

    std::cout << std::endl << d1 << " - " << d2 << " = " << d1 - d2 << std::endl;
}
