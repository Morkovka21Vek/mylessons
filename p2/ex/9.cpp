#include <iostream>

using namespace std;

int main() {
    int a, b, c, d, x, y;
    char dummychar;
    cout << "Вводите дроби в формате: \"x/y\"." << endl << "Введите 1-ю дробь: >>>";
    cin >> a >> dummychar >> b;
    cout << "Введите 2-ю дробь: >>>";
    cin >> c >> dummychar >> d;
    x = a*d + b*c;
    y = b*d;
    cout << "Сумма равна: >>" << x << "/" << y << endl;
    return 0;
}
