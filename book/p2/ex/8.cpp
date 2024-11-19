#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    long pop1 = 4654654, pop2 = 54654, pop3 = 456;
    cout << setfill('.')
		 << left << setw(7) << "Hello" << setfill('.') << right << setw(9) << "Bob" << endl
	     << left << setw(7) << "World" << setfill('.') << right << setw(9) <<  pop1 << endl
	     << left << setw(7) << "Bob"   << setfill('.') << right << setw(9) <<  pop2 << endl
	     << left << setw(7) << "Job"   << setfill('.') << right << setw(9) <<  pop3 << endl;
    return 0;
}
