#include <iostream>

int static_counter() {
    static int counter = 0;
    counter++;

    return counter - 1;
}

int gl_counter = 0;
int global_counter() {
    gl_counter++;

    return gl_counter - 1;
}

int main() {
    for (int i = 0; i < 21; i++) {
        std::cout << "static_counter: "   << static_counter()
                  << "\tglobal_counter: " << global_counter() << std::endl;
    }
}
