#include <iostream>

using std::cin;
using std::cout;
using std::endl;

int main() {
    float new_f;
    int old_f;
    int old_s;
    int old_p;

    cout << "Введите число десятичных фунтов: >>> ";
    cin >> new_f;

    old_f = static_cast<int>(new_f);
    old_s = static_cast<int>((new_f - old_f) * 20);
    old_p = static_cast<int>(((new_f - old_f) * 20 - old_s) * 12);

    cout << "В старой форме записи: >> £" << old_f << '.' << old_s << '.'
         << old_p << endl;
    return 0;
}
