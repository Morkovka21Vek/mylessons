#include <iostream>

int main() {
    double dollars;

    using namespace std;

    cout << "Введите сумму в долларах: >>> ";
    cin >> dollars;

    cout << dollars << "$ равны:" << endl
         << "£ >> " << (dollars * 1.487F) << endl  // фунты
         << "₣ >> " << (dollars * 0.172F) << endl  // франки
         << "ℳ  >> " << (dollars * 0.584F) << endl // немецкие марки
         << "¥ >> " << (dollars * 0.00955F) << endl; // японские йены
    return 0;
}
