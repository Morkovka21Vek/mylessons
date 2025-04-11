#include <iostream>

long hms_to_secs(int hours, int mins, int secs) {
    return hours*3600 + mins*60 + secs;
}

int main() {

    while (1) {
        std::cout << "Введите время в формате \"hh mm ss\": ";

        int hours, mins, secs;
        std::cin >> hours >> mins >> secs;

        std::cout << "Это равно " << hms_to_secs(hours, mins, secs) << " секундам." << std::endl << std::endl;
    }

    return 0;
}
