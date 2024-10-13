#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    long pop1 = 4654654, pop2 = 54654, pop3 = 456;
    cout    << std::left << setw(5) << "Hello" << std::right <<  setw(8) << "Bob" << endl
	    << std::left << setw(5) << "World" << std::right << setw(8) << pop1 << endl
	    << std::left << setw(5) << "Bob"   << std::right << setw(8) << pop2 << endl
	    << std::left << setw(5) << "Job"   << std::right << setw(8) << pop3 << endl;
    int x;
    std::cout << "x " << x << std::endl;
    return 0;
}
