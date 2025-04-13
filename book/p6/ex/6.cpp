#include <iostream>
#include <map>
#include <string>

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

        std::string _type;
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

    std::map<char, std::string> types {
        {'l', "laborer"   },
        {'s', "secretary" },
        {'m', "manager"   },
        {'a', "accountant"},
        {'e', "executive" },
        {'r', "researcher"}
    };

    std::map<char, std::string>::iterator it;
    it = types.find(inp);

    if (it == types.end()) {
        std::cout << "Значит он паразит? У нас такой должности нет!" << std::endl;
        this->_type = "NONE";
    } else
        this->_type = it->second;
}

void employee::putemploy() {
    std::cout << "ID сотрудника " << this->_num << ": " << this->_id << std::endl
              << "Его зарплата составляет " << this->_salary << '$' << std::endl
              << "Дата приёма на работу: " << this->_day << '/' << this->_month << '/' << this->_year << std::endl
              << "Его должность: " << this->_type;

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
