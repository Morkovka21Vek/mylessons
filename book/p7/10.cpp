#include <iostream>

class matrix {
  public:
    matrix(size_t uwidth, size_t uheight);
    void putel(size_t x, size_t y, int val);
    int getel(size_t x, size_t y) const;

  private:
    static const size_t WIDTH = 10;
    static const size_t HEIGHT = 10;
    int arr[WIDTH][HEIGHT];

    const size_t UWIDTH;
    const size_t UHEIGHT;
};

matrix::matrix(size_t uwidth, size_t uheight)
    : UWIDTH(uwidth), UHEIGHT(uheight) {}

int main() {
    matrix m1(3, 4);
    int temp = 12345;

    try {
        m1.putel(7, 4, temp);
        temp = m1.getel(7, 4);
    } catch (const std::out_of_range &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    return 0;
}

void matrix::putel(size_t x, size_t y, int val) {
    if (x < UWIDTH && y < UHEIGHT)
        arr[x][y] = val;
    else
        throw std::out_of_range("Index out of range");
}

int matrix::getel(size_t x, size_t y) const {
    if (x < UWIDTH && y < UHEIGHT)
        return arr[x][y];
    else
        throw std::out_of_range("Index out of range");
}
