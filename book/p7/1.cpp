#include <clocale>
#include <cstdlib>
#include <cwchar>
#include <iostream>
#include <ostream>

void reverseit(wchar_t *str, const size_t BUFFSIZE) {
    size_t len = wcsnlen(str, BUFFSIZE);

    for (size_t i = 0; i < len / 2; i++) {
        wchar_t temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {

    std::setlocale(LC_ALL, ""); //init()
    //line = getUserLine():
    //  printPrompt(prompt)
    //  line = getLine()
    //      getStr()
    //printUsetLine():
    //  Convert
    //  Print
    std::cout << "Введите строку: " << std::flush;

    const size_t BUFFSIZE = 100;
    wchar_t buff[BUFFSIZE];

    char chbuff[BUFFSIZE * 2] = {0};

    fgetws(buff, BUFFSIZE, stdin);

    std::cout << wcslen(buff) << std::endl;

    reverseit(buff, BUFFSIZE);

    std::wcstombs(chbuff, buff, sizeof(chbuff));
    std::cout << "Перевёрнутая строка: " << std::flush << chbuff << std::endl;

    return 0;
}
