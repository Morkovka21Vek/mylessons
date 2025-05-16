#ifndef _GPIO_H_
#define _GPIO_H_

void IRAM_ATTR button_tick1(void* arg);
void IRAM_ATTR button_tick2(void* arg);
int getButton_count1();
int getButton_count2();
void init_gpio();
bool getButton_level1();
bool getButton_level2();

#endif
