#include <iostream>
#include <ostream>

class Distance {
  public:
    Distance();
    Distance(int feet, float inches);
    Distance &operator+=(Distance d);
    Distance &operator/=(int divisor);
    friend std::ostream &operator<<(std::ostream &os, const Distance &obj);
    friend std::istream &operator>>(std::istream &in, Distance &d);

  private:
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

Distance &Distance::operator+=(Distance d) {
    float inchesSum = this->inches + d.inches;
    this->feet += d.feet + inchesSum / 12;
    this->inches = inchesSum - static_cast<int>(inchesSum) +
                   static_cast<int>(inchesSum) % 12;
    return *this;
}

Distance &Distance::operator/=(int divisor) {
    float fltfeet = (feet + inches / 12.0) / divisor;
    this->feet = static_cast<int>(fltfeet);
    this->inches = (fltfeet - static_cast<int>(fltfeet)) * 12.0;
    return *this;
}

int main() {
    const size_t BUFFSIZE = 100;
    Distance dist[BUFFSIZE];

    size_t buff_pos = 0;

    std::cout << "Вводите расстояния в формате \"feets inches\". Для выхода "
                 "нажмите Ctrl+D"
              << std::endl;
    do {
        std::cout << ">> " << std::flush;
        if (std::cin >> dist[buff_pos++])
            continue;

        buff_pos--;
        break;
    } while (buff_pos < BUFFSIZE);

    Distance sum;
    for (size_t i = 0; i < buff_pos; i++) {
        sum += dist[i];
    }
    sum /= buff_pos;

    std::cout << "\nСреднее значение: " << sum << std::endl;
}
