#include <iostream>
#include <ctype.h>

int main() {
    char inp;
   
    std::cout << "Input charaster please and press Enter" << std::endl; 
    std::cin >> inp;
    std::cout << "You put " << inp << " is lower " << !!islower(inp) << std::endl;
}
