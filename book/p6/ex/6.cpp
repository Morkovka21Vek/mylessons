#include <iostream>

enum etype {laborer, secretary, manager, accountant, executive, researcher};

class employee {
    public:
        employee(int num): _num(num)
        {}

        void getemploy();
        void putemploy();

    private:
        int _month, _day, _year;

        int _id;
        float _salary;
        int _num;

        etype _type;
};

void employee::getemploy() {
    char blackhole;

    std::cout << "Сотрудник " << this->_num << ':' << std::endl
              << "\tID: >>> ";         std::cin >> this->_id;
    std::cout << "\tЗарплата $: >>> "; std::cin >> this->_salary;

    std::cout << "\tДата приёма на работу: >>> ";
    std::cin >> this->_day >> blackhole >> this->_month >> blackhole >> this->_year;

    char inp;
    std::cout << "\tПервая буква должности(laborer, secretary, manager, accountant, executive, researcher):\n>>> "; std::cin >> inp;

    switch (inp){
        case 'l': this->_type = laborer;    break;
        case 's': this->_type = secretary;  break;
        case 'm': this->_type = manager;    break;
        case 'a': this->_type = accountant; break;
        case 'e': this->_type = executive;  break;
        case 'r': this->_type = researcher; break;
        default:
            std::cout << "Значит он паразит? У нас такой должности нет!" << std::endl;
    }
}

void employee::putemploy() {
    std::cout << "ID сотрудника " << this->_num << ": " << this->_id << std::endl
              << "Его зарплата составляет " << this->_salary << '$' << std::endl
              << "Дата приёма на работу: " << this->_day << '/' << this->_month << '/' << this->_year << std::endl
              << "Его должность: ";

    switch (this->_type) {
        case laborer:    std::cout << "laborer";    break;
        case secretary:  std::cout << "secretary";  break;
        case manager:    std::cout << "manager";    break;
        case accountant: std::cout << "accountant"; break;
        case executive:  std::cout << "executive";  break;
        case researcher: std::cout << "researcher"; break;
    }

    std::cout << std::endl << std::endl;

}


int main () {
    employee emp1(1), emp2(2), emp3(3);

    emp1.getemploy();
    emp2.getemploy();
    emp3.getemploy();

    emp1.putemploy();
    emp2.putemploy();
    emp3.putemploy();

    return 0;
}
