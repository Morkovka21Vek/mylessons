#include <clocale>
#include <iostream>

void reverseit(wchar_t *str, const size_t BUFFSIZE) {
    size_t len = wcsnlen(str, BUFFSIZE);

    for (size_t i = 0; i < len / 2; i++) {
        wchar_t temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

void printPrompt(const char *str) { std::cout << str << std::flush; }

void getLine(wchar_t *buff, size_t BUFFSIZE) { fgetws(buff, BUFFSIZE, stdin); }

void getUserLine(wchar_t *buff, size_t BUFFSIZE) {
    printPrompt("Введите строку: ");
    getLine(buff, BUFFSIZE);
}

void init() { std::setlocale(LC_ALL, ""); }

void printLine(const char *str) {
    std::cout << "Перевёрнутая строка: " << str << std::endl;
}

void convertToChar(char *chbuff, const wchar_t *buff, size_t BUFFSIZE) {
    std::wcstombs(chbuff, buff, BUFFSIZE * 2);
}

void printUserLine(const wchar_t *buff, size_t BUFFSIZE) {
    char *chbuff = new char[BUFFSIZE * 2];
    convertToChar(chbuff, buff, BUFFSIZE);
    printLine(chbuff);
    delete[] chbuff;
}

int main() {
    const size_t BUFFSIZE = 100;
    wchar_t buff[BUFFSIZE];

    init();
    getUserLine(buff, BUFFSIZE);

    reverseit(buff, BUFFSIZE);

    printUserLine(buff, BUFFSIZE);

    return 0;
}
