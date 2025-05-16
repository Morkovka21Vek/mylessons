#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_attr.h"
#include "esp_timer.h"

static int button_count1 = 0;
static int button_count2 = 0;

static volatile uint32_t last_interrupt_time1 = 0;
static volatile uint32_t last_interrupt_time2 = 0;

void IRAM_ATTR button_tick1(void* arg) {
  uint32_t current_time = esp_timer_get_time() / 1000;
  if (current_time - last_interrupt_time1 > 100) {
    button_count1++;
    last_interrupt_time1 = current_time;
  }
}
void IRAM_ATTR button_tick2(void* arg) {
  uint32_t current_time = esp_timer_get_time() / 1000;
  if (current_time - last_interrupt_time2 > 100) {
    button_count2++;
    last_interrupt_time2 = current_time;
  }
}

int getButton_count1() {
    return button_count1;
}

int getButton_count2() {
    return button_count2;
}

bool getButton_level1() {
    return !gpio_get_level(CONFIG_DOWN_GPIO_NUM);
}

bool getButton_level2() {
    return !gpio_get_level(CONFIG_UP_GPIO_NUM);
}

void init_gpio() {
    gpio_set_direction(CONFIG_DOWN_GPIO_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_DOWN_GPIO_NUM, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(CONFIG_DOWN_GPIO_NUM, GPIO_INTR_NEGEDGE);

    gpio_set_direction(CONFIG_UP_GPIO_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_UP_GPIO_NUM, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(CONFIG_UP_GPIO_NUM, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(CONFIG_DOWN_GPIO_NUM, button_tick1, NULL);
    gpio_isr_handler_add(CONFIG_UP_GPIO_NUM, button_tick2, NULL);
}
