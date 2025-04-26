#include "esp_log.h"
#include "driver/uart.h"
#include "uart.h"
#include <errno.h>

#define TX_PIN 13
#define RX_PIN 15

#define TAG "UART.c"

// Инициализация UART
void init_uart() {
    unsigned int baud_rate = 9600;
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

ssize_t uart_read_line(uart_port_t uart_port, char *buffer, size_t max_len, uint32_t timeout_ms, char sep) {
    size_t index = 0;
    uint8_t byte;

    while (index < max_len - 1) {
        // Читаем по 1 байту с таймаутом
        int len = uart_read_bytes(uart_port, &byte, 1, pdMS_TO_TICKS(timeout_ms));

        if (len <= 0) {
            // Таймаут или ошибка
            buffer[index] = '\0';
            errno = ETIMEDOUT;
            return -1;
        }

        if (byte == sep) {
            buffer[index] = '\0';  // Завершаем строку
            return index-1;
        } else {
            buffer[index++] = byte;
        }
    }

    buffer[index] = '\0';  // На случай переполнения
    errno = EOVERFLOW;
    return -1;
}
