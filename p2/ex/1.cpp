#include <iostream>
#define EXIT_SUCCESS 0

// int main() {
//     using namespace std;
//     const float Gal = 7.481;
//     float inp;
//     cout << "Gal: >>";
//     cin >> inp;
//     float out = inp/Gal;
//     cout << "F3 = " << out << endl;
//     return 0;
// }

int main(){

	// значение из учебника страница 88
	const float gal = 7.481;
	float inp;
        float out;

	std::cout << "Enter galons please" << std::endl
                  << "Gal: >> ";
        std::cin  >> inp;	

	out = inp/gal;
	
	std::cout << "In " << inp << " gallons " << out << " foots" << std::endl;

	return (EXIT_SUCCESS);
}
