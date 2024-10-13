// применение cin and \n
#include <iostream>
int main(){
    int ftemp;
    std::cout << "Input tempirature on F: >>>";
    std::cin >> ftemp;
    int ctemp = (ftemp-32)*5/9;
    std::cout << "Tempirature on C = " << ctemp << '\n';
    return 0;
}
