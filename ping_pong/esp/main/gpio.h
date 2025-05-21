#ifndef _GPIO_H_
#define _GPIO_H_

#include <stdbool.h>
#include <stdint.h>

void init_gpio();
size_t getButton_count(size_t button_num);
bool getButton_level(size_t button_num);

#endif
