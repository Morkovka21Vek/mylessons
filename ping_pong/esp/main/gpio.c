#include "driver/gpio.h"
#include "esp_attr.h"
#include "esp_timer.h"
#include "sdkconfig.h"

#define DEBOUNCE_TIME_MS 100

typedef struct {
    uint32_t count;
    uint32_t last_interrupt_time;
    int gpio_num;
} button_t;

static button_t buttons[2] = {{.gpio_num = CONFIG_DOWN_GPIO_NUM, .count = 0},
                              {.gpio_num = CONFIG_UP_GPIO_NUM, .count = 0}};

void IRAM_ATTR button_tick(void *arg) {
    size_t button_num = (size_t)arg;
    uint32_t current_time = esp_timer_get_time() / 1000;
    if (current_time - buttons[button_num].last_interrupt_time >
        DEBOUNCE_TIME_MS) {
        buttons[button_num].count++;
        buttons[button_num].last_interrupt_time = current_time;
    }
}

int getButton_count(size_t button_num) {
    return (button_num < sizeof(buttons) / sizeof(button_t))
               ? buttons[button_num].count
               : 0;
}

bool getButton_level(size_t button_num) {
    return (button_num < sizeof(buttons) / sizeof(button_t))
               ? !gpio_get_level(buttons[button_num].gpio_num)
               : 0;
}

void init_gpio() {
    gpio_install_isr_service(0);

    for (size_t i = 0; i < sizeof(buttons) / sizeof(button_t); i++) {
        gpio_set_direction(buttons[i].gpio_num, GPIO_MODE_INPUT);
        gpio_set_pull_mode(buttons[i].gpio_num, GPIO_PULLUP_ONLY);
        gpio_set_intr_type(buttons[i].gpio_num, GPIO_INTR_NEGEDGE);
        gpio_isr_handler_add(buttons[i].gpio_num, button_tick, (void *)i);
    }
}
