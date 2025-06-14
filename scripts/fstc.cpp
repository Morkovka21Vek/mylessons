#include <stdlib.h>

int main(int args_count, const char *args[]) {
    for (int i = 1; i < args_count; i++)
        system(args[i]);
    return 0;
}
