#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define but_left_down_pin 0
#define but_left_up_pin 1

#define but_right_down_pin 2
#define but_right_up_pin 3

void app_main(void)
{
  //gpio_pad_select_gpio(but_left_pin);
  gpio_set_direction(but_left_down_pin, GPIO_MODE_INPUT);
  gpio_set_pull_mode(but_left_down_pin, GPIO_PULLUP_ONLY);

  gpio_set_direction(but_left_up_pin, GPIO_MODE_INPUT);
  gpio_set_pull_mode(but_left_up_pin, GPIO_PULLUP_ONLY);

  gpio_set_direction(but_right_down_pin, GPIO_MODE_INPUT);
  gpio_set_pull_mode(but_right_down_pin, GPIO_PULLUP_ONLY);

  gpio_set_direction(but_right_up_pin, GPIO_MODE_INPUT);
  gpio_set_pull_mode(but_right_up_pin, GPIO_PULLUP_ONLY);

  printf("$");
  fflush(stdout);

  while(1) {
    //int level = gpio_get_level(but_left_down_pin);
    //printf("%d ", level);
    if(!gpio_get_level(but_left_down_pin))
      printf("z");
    if(!gpio_get_level(but_left_up_pin))
      printf("a");

    if(!gpio_get_level(but_right_down_pin))
      printf("/");
    if(!gpio_get_level(but_right_up_pin))
      printf("\'");

    fflush(stdout);

    if(!gpio_get_level(but_left_down_pin) || !gpio_get_level(but_left_up_pin)
        || !gpio_get_level(but_right_down_pin) || !gpio_get_level(but_right_up_pin))
      vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}
