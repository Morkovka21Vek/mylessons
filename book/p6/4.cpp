#include <iostream>
#include <ostream>

class employee {
  public:
    explicit employee(int num);

    void answerData();
    friend std::ostream &operator<<(std::ostream &os, const employee &obj);

  private:
    int _id = -1;
    float _salary = -1;
    int _num;
};

employee::employee(int num) : _num(num) {}

void employee::answerData() {
    std::cout << "Сотрудник " << this->_num << ':' << std::endl << "\tID: >>> ";
    std::cin >> _id;
    std::cout << "\tЗарплата $: >>> ";
    std::cin >> _salary;
}

std::ostream &operator<<(std::ostream &os, const employee &obj) {
    return os << "ID сотрудника " << obj._num << "- " << obj._id
              << "; Его зарплата составляет " << obj._salary << '$';
}

int main() {
    employee emp1(1);
    employee emp2(2);
    employee emp3(3);

    emp1.answerData();
    emp2.answerData();
    emp3.answerData();

    std::cout << std::endl
              << emp1 << std::endl
              << emp2 << std::endl
              << emp3 << std::endl;

    return 0;
}
