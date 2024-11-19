#include <iostream>

using std::cout;
using std::endl;
using std::cin;

struct sterling {
  int pounds;
  int shillings;
  int pence;
};

int main() {
    double new_f;
    sterling ster;
    char spaceChar;

    cout << "Введите число десятичных фунтов: >>> ";
    cin >> new_f;

    ster.pounds = static_cast<int>(new_f);
    ster.shillings = static_cast<int>((new_f - ster.pounds) * 20);
    ster.pence = static_cast<int>(((new_f - ster.pounds) * 20 - ster.shillings) * 12);

    cout << "В старой форме записи: >> £" << ster.pounds << '.' << ster.shillings << '.' << ster.pence << endl;
    return 0;
}

