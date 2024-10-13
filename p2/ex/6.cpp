#include <iostream>

using namespace std;

int main() {
    double dollars;

    cout << "☢ 😀 Введите сумму в долларах: >>> ";
    cin >> dollars;
    
    cout << "фунты >> "          << (dollars*1.487F)   << endl
         << "франки >> "         << (dollars*0.172F)   << endl
         << "немецкие марки >> " << (dollars*0.584F)   << endl
         << "японские йены>> "   << (dollars*0.00955F) << endl;
    return 0;
}
