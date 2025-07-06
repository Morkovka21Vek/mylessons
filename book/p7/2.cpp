#include <iostream>
#include <ostream>
#include <string>

class employee {
  public:
    friend std::ostream &operator<<(std::ostream &os, const employee &obj);
    bool getName();
    void getNum();

  private:
    std::string name;
    long num;
};

std::ostream &operator<<(std::ostream &os, const employee &obj) {
    return os << "Имя содрудника с номером " << obj.num << " - " << obj.name;
}

bool employee::getName() {
    getline(std::cin, name);
    return name.length() > 0;
}

void employee::getNum() {
    std::cin >> num;
    std::cin.ignore();
}

int main() {

    const size_t BUFFSIZE = 100;
    employee emps[BUFFSIZE];

    size_t empNum = 0;

    do {
        std::cout << "Введите данные сотрудника " << empNum << ": " << std::endl
                  << "Имя(для прекращения нажмите Enter): " << std::flush;

        if (!emps[empNum].getName())
            break;

        std::cout << "Номер: " << std::flush;

        emps[empNum].getNum();

        empNum++;
    } while (empNum < BUFFSIZE);

    for (size_t i = 0; i < empNum; i++) {
        std::cout << "Позиция " << i << ": " << emps[i] << std::endl;
    }

    return 0;
}
