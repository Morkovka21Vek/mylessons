#include <iostream>

struct sterling {
    int pounds;
    int shillings;
    int pence;
};

sterling askUser() {
    sterling ster;
    std::cin >> ster.pounds >> ster.shillings >> ster.pence;

    return ster;
}

sterling summSterling(sterling ster1, sterling ster2) {
    sterling sterOut;

    sterOut.pence = (ster1.pence + ster2.pence) % 12;
    sterOut.shillings = (ster1.pence + ster2.pence) / 12;

    sterOut.pounds =
        (sterOut.shillings + ster1.shillings + ster2.shillings) / 20;
    sterOut.shillings =
        (sterOut.shillings + ster1.shillings + ster2.shillings) % 20;

    sterOut.pounds += ster1.pounds + ster2.pounds;

    return sterOut;
}

void showSterling(sterling ster) {
    std::cout << "Ответ: £" << ster.pounds << '.' << ster.shillings << '.'
              << ster.pence << std::endl;
}

int main() {
    sterling ster1;
    sterling ster2;

    std::cout << "Введите первую сумму: ";
    ster1 = askUser();
    std::cout << "Введите вторую сумму: ";
    ster2 = askUser();

    showSterling(summSterling(ster1, ster2));

    return 0;
}
