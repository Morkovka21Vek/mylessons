#include "esp_log.h"
#include "driver/uart.h"
#include "uart.h"

#define TX_PIN 13
#define RX_PIN 15

#define TAG "UART.c"

// Инициализация UART
void init_uart() {
    unsigned int baud_rate = 115200;
    ESP_LOGI(TAG, "Run uart on port %d speed %d", UART_NUM, baud_rate);
    uart_config_t uart_config = {
        .baud_rate = baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}
