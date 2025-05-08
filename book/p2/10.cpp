#include <iostream>

using namespace std;

int main() {
    float old_f;
    float old_s;
    float old_p;
    float new_f;

    char spaceChar;
    cout << "Данная программа переводит денежную сумму из старой английской "
            "денежной сисемы в новую.\nВводите сумму вмето \"£7.17.9\" так: "
            "\"7/17/9\".\nВведите сумму в старом формате: >>> ";
    cin >> old_f >> spaceChar >> old_s >> spaceChar >> old_p;

    new_f = old_f + (old_s / 20) + (old_p / 20 / 12);
    cout << "Сумма в десятичных фунтах: >> £" << new_f << endl;

    return 0;
}
