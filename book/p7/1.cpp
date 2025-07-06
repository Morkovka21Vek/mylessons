#include <locale>
#include <wchar.h>

void reverseit(wchar_t *str) {
    size_t len = wcslen(str);

    for (size_t i = 0; i < len / 2; i++) {
        wchar_t temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

int main() {
    std::setlocale(LC_ALL, "");

    wprintf(L"Введите строку: ");

    const size_t BUFFSIZE = 100;
    wchar_t buff[BUFFSIZE]; // С char не работает кириллица

    fgetws(buff, BUFFSIZE, stdin);

    reverseit(buff);

    wprintf(L"Перевёрнутая строка: %ls\n", buff);

    return 0;
}
