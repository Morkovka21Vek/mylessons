#include <iostream>
using namespace std;
int main(){
    int signedVar = 1500000000;
    unsigned int unsignVar = 1500000000;
    signedVar = (signedVar * 2) / 3;
    unsignVar = (unsignVar * 2) / 3;
    cout << "signedVar = " << signedVar << endl;
    cout << "unsignVar = " << unsignVar << endl;
    return 0;
}
