#include <iostream>

struct employee {
    int id;
    float salary;
};

int main() {

    employee emp1;
    employee emp2;
    employee emp3;

    std::cout << "Сотрудник 1:" << std::endl << "\tID: >>> ";
    std::cin >> emp1.id;
    std::cout << "\tЗарплата $: >>> ";
    std::cin >> emp1.salary;

    std::cout << "Сотрудник 2:" << std::endl << "\tID: >>> ";
    std::cin >> emp2.id;
    std::cout << "\tЗарплата $: >>> ";
    std::cin >> emp2.salary;

    std::cout << "Сотрудник 3:" << std::endl << "\tID: >>> ";
    std::cin >> emp3.id;
    std::cout << "\tЗарплата $: >>> ";
    std::cin >> emp3.salary;

    std::cout << std::endl;

    std::cout << "ID сотрудника 1 - " << emp1.id << "; Его зарплата составляет "
              << emp1.salary << '$' << std::endl;
    std::cout << "ID сотрудника 2 - " << emp2.id << "; Его зарплата составляет "
              << emp2.salary << '$' << std::endl;
    std::cout << "ID сотрудника 3 - " << emp3.id << "; Его зарплата составляет "
              << emp3.salary << '$' << std::endl;

    return 0;
}
