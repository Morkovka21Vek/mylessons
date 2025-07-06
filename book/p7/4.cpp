#include <iostream>

size_t maxint(const int* buff, size_t buffsize) {
    size_t maxIndex = 0;
    for (size_t i = 1; i < buffsize; i++)
        if (buff[maxIndex] < buff[i])
            maxIndex = i;

    return maxIndex;
}

int main() {

    const size_t BUFFSIZE = 100;
    int buff[BUFFSIZE];
    size_t buff_pos = 0;

    std::cout << "Для выхода используйте Ctrl+D" << std::endl;
    do {
        std::cout << "Введите целое число: " << std::flush;
        if (std::cin >> buff[buff_pos++])
            continue;
        buff_pos--;
        break;
    } while (buff_pos < BUFFSIZE);

    size_t maxIndex = maxint(buff, buff_pos);

    std::cout << "\nНаибольшее число: " << buff[maxIndex]
              << " (индекс: " << maxIndex << ')' << std::endl;

    return 0;
}
