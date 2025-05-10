#include <iostream>

struct UserProfile {
    const char *name;
    int adge;
};

void printUserProfile(struct UserProfile &up) {
    std::cout << "Name: " << up.name << " addr: " << &up.name << std::endl
              << "Age: " << up.adge << " addr: " << &up.adge << std::endl;
}

void printUserProfile2(struct UserProfile up) {
    std::cout << "Name: " << up.name << " addr: " << &up.name << std::endl
              << "Age: " << up.adge << " addr: " << &up.adge << std::endl;
}
void test() {
    int i = 0;
  for(;i < 10
}
int main() {
    int p1;
    p1 = 12;

    {
        UserProfile p1 = {.name = "Vladimir", .adge = 13};
        printUserProfile(p1);
        printUserProfile(p1);
        printUserProfile2(p1);
    }

    std::cout << "P1: " << p1 << std::endl;

    return 0;
}
