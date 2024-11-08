#include <iostream>

struct employee {
  int id;
  float salary;
  Date date;
  etype type;
};

struct Date {
  int day;
  int month;
  int year;
};

enum etype {laborer, secretary, manager, accountant, executive, researcher};

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

void 

int main () {

  char slash, inp_etype;
  
  employee emp1, emp2, emp3;

  std::cout << "Правила ввода: " << std::endl
    << "\nДату вводить в формате dd/mm/yyyy (левые нули можно отбросить)" << std::endl
    <<std::endl;


  std::cout << "Сотрудник 1:" << std::endl
    << "\tID: >>> "; std::cin >> emp1.id;
  std::cout << "\tЗарплата $: >>> "; std::cin >> emp1.salary;
  std::cout << "Введите первую букву должности (laborer, secretary, manager, accountant, executive, researcher):"
    << std::endl << ">>> ";
  std::cin >> inp_etype;

  std::cout << "\tВведите дату принятия на работу: >>> "; 
  std::cin >> emp1.date.day >> slash >> emp1.date.month >> slash >> emp1.date.year;


  std::cout << std::endl;

  std::cout << "ID сотрудника 1 - " << emp1.id << "; Его зарплата составляет " << emp1.salary << '$' << std::endl;
  //std::cout << date1.day << '/' << date1.month << '/' << date1.year << std::endl;
  return 0;
}

