#include <iostream>

enum class etype {
    laborer,
    secretary,
    manager,
    accountant,
    executive,
    researcher
};

int main() {
    char inp;
    etype type1;

    std::cout << "Введите первую букву должности (laborer, secretary, manager, "
                 "accountant, executive, researcher):"
              << std::endl
              << ">>> ";
    std::cin >> inp;

    switch (inp) {
    case 'l':
        type1 = etype::laborer;
        break;
    case 's':
        type1 = etype::secretary;
        break;
    case 'm':
        type1 = etype::manager;
        break;
    case 'a':
        type1 = etype::accountant;
        break;
    case 'e':
        type1 = etype::executive;
        break;
    case 'r':
        type1 = etype::researcher;
        break;
    default:
        std::cout << "Error" << std::endl;
        std::exit(1);
    }

    std::cout << "Полное название должности: ";

    switch (type1) {
    case etype::laborer:
        std::cout << "laborer";
        break;
    case etype::secretary:
        std::cout << "secretary";
        break;
    case etype::manager:
        std::cout << "manager";
        break;
    case etype::accountant:
        std::cout << "accountant";
        break;
    case etype::executive:
        std::cout << "executive";
        break;
    case etype::researcher:
        std::cout << "researcher";
        break;
    }
    std::cout << std::endl;

    return 0;
}
