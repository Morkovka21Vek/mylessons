#include <iostream>

using namespace std;

int main() {
    float old_f, old_s, old_p, new_f;
    char spaceChar;

    cout << "Вводите сумму вмето \"\x9C" << "7.17.9\" так: \"7/17/9\".\nВведите сумму в старом формате: >>>";
    cin >> old_f >> spaceChar >> old_s >> spaceChar >> old_p;
    
    new_f = old_f + (old_s / 20) + (old_p / 20 / 12);

    cout << "Сумма в десятичных фунтах: >> \x9C" << new_f << endl;
    return 0;
}
