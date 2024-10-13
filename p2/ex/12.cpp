#include <iostream>

using std::cout;
using std::endl;
using std::cin;

int main() {
    float new_f;
    int old_f, old_s, old_p;
    char spaceChar;

    cout << "Введите число десятичных фунтов: >>> ";
    cin >> new_f;

    old_f = static_cast<int>(new_f);
    old_s = static_cast<int>((new_f - old_f) * 20);
    old_p = (new_f * 20 * 12 - old_f * 20 * 12 - (old_s * 12));

    //new_f = old_f + (old_s / 20) + (old_p / 20 / 12);
    //cout << "Сумма в десятичных фунтах: >> £" << new_f << endl;

    cout << "В старой форме записи: >> £" << old_f << '.' << old_s << '.' << old_p << endl;
    return 0;
}
