#include <fcntl.h>
#include <iostream>

class safearay {
  public:
    int &operator[](size_t);

  private:
    static const int LIMIT = 10;
    int arr[LIMIT];
};

int &safearay::operator[](size_t index) {
    if (index >= LIMIT)
        throw std::out_of_range("Index out of range");
    return arr[index];
}

int main() {
    safearay sa1;
    int temp = 12345;

    try {
        sa1[7] = temp;
        temp = sa1[7];

        temp = sa1[10];
    } catch (const std::out_of_range &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}
