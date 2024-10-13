#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    long pop1 = 4654654, pop2 = 54654, pop3 = 456;
    cout << setfill('.') << setw(2) << "Hello" << setfill('.') << setw(9) << "Bob" << endl
	    << setfill('.') << setw(2) << "World" << setfill('.') << setw(9) << pop1 << endl
	    << setfill('.') << setw(2) << "Bob.." << setfill('.') << setw(9) << pop2 << endl
	    << setfill('.') << setw(2) << "Job.." << setfill('.') << setw(9) << pop3 << endl;
    return 0;
}
