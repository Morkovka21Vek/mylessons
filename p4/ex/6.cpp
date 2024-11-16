#include <iostream>

enum etype {laborer, secretary, manager, accountant, executive, researcher};

int main() {

  char inp;
  etype type1;

  std::cout << "Введите первую букву должности (laborer, secretary, manager, accountant, executive, researcher):"
    << std::endl << ">>> ";
  std::cin >> inp;

  switch (inp){
    case 'l': type1 = laborer; break; 
    case 's': type1 = secretary; break; 
    case 'm': type1 = manager; break; 
    case 'a': type1 = accountant; break; 
    case 'e': type1 = executive; break; 
    case 'r': type1 = researcher; break; 
  }

  std::cout << "Полное название должности: ";

  switch (type1) {
    case laborer:    std::cout << "laborer";    break;
    case secretary:  std::cout << "secretary";  break;
    case manager:    std::cout << "manager";    break;
    case accountant: std::cout << "accountant"; break;
    case executive:  std::cout << "executive";  break;
    case researcher: std::cout << "researcher"; break;
  }
  std::cout << std::endl;

  return 0;
}
