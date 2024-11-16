#include <iostream>

struct Date {
  int day;
  int month;
  int year;
};

enum etype {laborer, secretary, manager, accountant, executive, researcher};

struct employee {
  int id;
  float salary;
  Date date;
  etype type;
};

 /* 
    */

void printEmp(employee emp, int number) {
  std::cout << "ID сотрудника " << number << " - " << emp.id
    << std::endl << "Его зарплата составляет " << emp.salary << '$' 
    << std::endl << "Его должность: ";
  switch (emp.type) {
    case laborer:    std::cout << "laborer";    break;
    case secretary:  std::cout << "secretary";  break;
    case manager:    std::cout << "manager";    break;
    case accountant: std::cout << "accountant"; break;
    case executive:  std::cout << "executive";  break;
    case researcher: std::cout << "researcher"; break;
  }
  std::cout << std::endl << "Дата когда он поступил на работу: " << emp.date.day << '/' << emp.date.month << '/' << emp.date.year << std::endl << std::endl;

}

etype get_etype(char inp) {
  etype type1;
  switch (inp){
    case 'l': type1 = laborer; break; 
    case 's': type1 = secretary; break; 
    case 'm': type1 = manager; break; 
    case 'a': type1 = accountant; break; 
    case 'e': type1 = executive; break; 
    case 'r': type1 = researcher; break; 
  }
  return type1;
}

employee generateEmp(int number){
  employee emp;
  char temp_inp_etype, slash;
  std::cout << "Сотрудник " << number << ':' << std::endl
    << "\tID: >>> "; std::cin >> emp.id;
  std::cout << "\tЗарплата $: >>> "; std::cin >> emp.salary;
  std::cout << "Введите первую букву должности (laborer, secretary, manager, accountant, executive, researcher):"
    << std::endl << ">>> "; std::cin >> temp_inp_etype;

  emp.type = get_etype(temp_inp_etype);

  std::cout << "\tВведите дату принятия на работу: >>> "; 
  std::cin >> emp.date.day >> slash >> emp.date.month >> slash >> emp.date.year;
  return emp;
}

int main () {

  employee emp1, emp2, emp3;

  std::cout << "Правила ввода: " << std::endl
    << "\nДату вводить в формате dd/mm/yyyy (левые нули можно отбросить)" << std::endl
    <<std::endl;

  emp1 = generateEmp(1);
  emp2 = generateEmp(2);
  emp3 = generateEmp(3);

  printEmp(emp1, 1);
  printEmp(emp2, 2);
  printEmp(emp3, 3);

  return 0;
}
