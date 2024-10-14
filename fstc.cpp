#include <iostream>

int main(int args_count, char *args[]) {
	for (int i = 1; i < args_count; i++)
		system(args[i]);
	return 0;
}
