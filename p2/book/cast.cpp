#include <iostream>

using namespace std;

int main(){
    int intVar = 1500000000;
    //int intVar = 15000000000;
    intVar = (intVar * 10) / 11;
    cout << "intVar = " << intVar << endl;

    int intVar2 = 1500000000;
    //intVar = 15000000000;
    intVar2 = (static_cast<double>(intVar2) * 10) / 11;
    cout << "intVar = " << intVar2 << endl;

    return 0;
}
