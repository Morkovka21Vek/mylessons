#include <iostream>
#include <iomanip>
using namespace std;
int main(){
    long pop1 = 8425785, pop2 = 47, pop3 = 9761;
    cout << setw(9) << left << "Город " << setw(12) << right
	    << "Население " << endl	    
    << setw(9) << left << "Москва" << setw(12) << right << pop1 << endl
    << setw(9) << left << "Киров" << setw(12) << right << pop2 << endl
    << setw(9) << left << "Угрюмовка" << setw(12) << right << pop3 << endl;
    return 0;
}
