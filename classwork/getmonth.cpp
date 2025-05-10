#include <iostream>

int printMonths(int month_num) {
    int result = 0;
    const char *monts[] = {"Январь",   "Февраль", "Март",   "Апрель",
                           "Май",      "Июнь",    "Июль",   "Август",
                           "Сентябрь", "Октябрь", "Ноябрь", "Декарь"};
    
    if (const int monts_len = sizeof(monts) / sizeof(char *); !((month_num - 1) >= 0 && (month_num < monts_len))) {
        result = -1;
    } else {
        std::cout << monts[month_num - 1] << std::endl;
    }
    return (result);
}

int main() {
    int number;

    std::cout << "Введите пожалуйста номер месяца от 1 до 12:\n>>>";
    std::cin >> number;

    std::cout << "Это месяц: ";
    printMonths(number);

    switch (number) {
    case 1:
        std::cout << "Январь";
        break;
    case 2:
        std::cout << "Февраль";
        break;
    case 3:
        std::cout << "Март";
        break;
    case 4:
        std::cout << "Апрель";
        break;
    case 5:
        std::cout << "Май";
        break;
    case 6:
        std::cout << "Июнь";
        break;
    case 7:
        std::cout << "Июль";
        break;
    case 8:
        std::cout << "Август";
        break;
    case 9:
        std::cout << "Сентябрь";
        break;
    case 10:
        std::cout << "Октябрь";
        break;
    case 11:
        std::cout << "Ноябрь";
        break;
    case 12:
        std::cout << "Декабрь";
        break;
    default:
        std::cout << "Неверный номер месяца!";
    }
    std::cout << std::endl;

    return 0;
}
