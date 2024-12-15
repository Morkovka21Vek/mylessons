#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define but_left_down_pin 0
#define but_left_up_pin 1

#define but_right_down_pin 2
#define but_right_up_pin 3
#define print_symbol_by_pin(pin,symbol) {if(!gpio_get_level(pin)) printf(symbol);}

void app_main(void)
{
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

    print_symbol_by_pin(but_left_down_pin,  "z");
    print_symbol_by_pin(but_left_up_pin,    "a");
    print_symbol_by_pin(but_right_down_pin, "/");
    print_symbol_by_pin(but_right_up_pin,   "\'");

    fflush(stdout);

    if(1 || !gpio_get_level(but_left_down_pin) 
         || !gpio_get_level(but_left_up_pin)
         || !gpio_get_level(but_right_down_pin) 
         || !gpio_get_level(but_right_up_pin)){

      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
}
