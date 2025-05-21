#include <sys/types.h>
#include "driver/uart.h"

#define UART_NUM UART_NUM_1
void init_uart();
ssize_t uart_read_line(uart_port_t uart_port, char *buffer, size_t max_len, uint32_t timeout_ms, char sep);
