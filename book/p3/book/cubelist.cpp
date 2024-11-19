#include <iostream>
#include <iomanip>

using std::cout;
using std::setw;
using std::endl;
using std::left;

int main() {
	for (int numb=1; numb<=10; numb++) {
		cout << left << setw(4) << numb;
		int cube = numb*numb*numb;
		cout << left << setw(6) << cube << endl;
	}
	return 0;
}
