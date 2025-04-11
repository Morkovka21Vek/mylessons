#include <iostream>

struct Distance {
    int feet;
    float inches;
};

Distance biggest(Distance d1, Distance d2) {
    return ((d1.feet * 12 + d1.inches) > (d2.feet * 12 + d2.inches)) ? d1 : d2;
}

int main() {

    Distance d1 = {10, 20}, d2 = {10, 30};
    Distance out = biggest(d1, d2);

    std::cout << "Из {" << d1.feet << ", " << d1.inches << "} и {" << d2.feet << ", " << d2.inches << "} наибольшее - {" << out.feet << ", " << out.inches << '}' << std::endl;

    return 0;
}
