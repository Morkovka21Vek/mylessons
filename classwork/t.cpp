#include <iostream>

struct UserProfile {
    const char *name;
    int age;
};

void printUserProfile(const UserProfile &up) {
    std::cout << "Name: " << up.name << " addr: " << &up.name << std::endl
              << "Age: " << up.age << " addr: " << &up.age << std::endl;
}

void printUserProfile2(struct UserProfile up) {
    std::cout << "Name: " << up.name << " addr: " << &up.name << std::endl
              << "Age: " << up.age << " addr: " << &up.age << std::endl;
}
int main() {
    int p1;
    p1 = 12;

    {
        UserProfile p1 = {.name = "Vladimir", .age = 13};
        printUserProfile(p1);
        printUserProfile(p1);
        printUserProfile2(p1);
    }

    std::cout << "P1: " << p1 << std::endl;

    return 0;
}
