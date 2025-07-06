#include <iostream>

class safearay {
  public:
    safearay(size_t min, size_t max);
    ~safearay();
    int &operator[](size_t);

  private:
    int *arr;
    const size_t min;
    const size_t max;
};

safearay::~safearay() {
  delete[] arr;
  arr = nullptr;
}

safearay::safearay(size_t min, size_t max): min(min), max(max) {
  arr = new int[max - min + 1];
}

int &safearay::operator[](size_t index) {
    if (index < min || index >= max)
        throw std::out_of_range("Index out of range");
    return arr[index - min];
}

int main() {
    safearay sa1(10, 20);
    int temp = 12345;

    try {
        sa1[17] = temp;
        temp = sa1[17];
        sa1[15] = 1;
        std::cout << temp << std::endl;
        std::cout << sa1[15] << std::endl;

        //temp = sa1[100];
    } catch (const std::out_of_range &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
