#include <iostream>
#include <ostream>

class employee {
    public:
        explicit employee(int num);

        void answerData();
        void getValues(int& num, int& id, float& salary) const;

    private:
        int _id = -1;
        float _salary = -1;
        int _num;
};

employee::employee(int num): _num(num)
{}

void employee::getValues(int& num, int& id, float& salary) const{
    num =    this->_num;
    id =     this->_id;
    salary = this->_salary;
}

void employee::answerData() {
    std::cout << "Сотрудник " << this->_num << ':' << std::endl
              << "\tID: >>> ";         std::cin >> _id;
    std::cout << "\tЗарплата $: >>> "; std::cin >> _salary;
}

std::ostream& operator<<(std::ostream& os, const employee& obj) {
    int num;
    int id;
    float salary;
    obj.getValues( num, id, salary );

    os << "ID сотрудника " << num << "- " << id << "; Его зарплата составляет " << salary << '$';
    return os;
}



int main () {
    employee emp1(1);
    employee emp2(2);
    employee emp3(3);

    emp1.answerData();
    emp2.answerData();
    emp3.answerData();

    std::cout << std::endl << emp1
              << std::endl << emp2
              << std::endl << emp3 << std::endl;

    return 0;
}
