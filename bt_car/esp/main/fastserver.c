#ifdef ESP_PLATFORM
    #include "esp_log.h"
    #include "driver/uart.h"
    #include "uart.h"
    #include <lwip/sockets.h>
#else
    #define ESP_LOGI(TAG, str, ...) printf("\033[0;32mI %s: %s\033[0m", TAG, str, __VA_ARGS__);
    #define ESP_LOGW(TAG, str, ...) printf("\033[0;33mW %s: %s\033[0m", TAG, str, __VA_ARGS__);
    #define ESP_LOGE(TAG, str, ...) printf("\033[0;31mE %s: %s\033[0m", TAG, str, __VA_ARGS__);
    #include <sys/socket.h>
#endif
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const char* TAG = "FASTSERVER.c";
#define PORT 81

//ssize_t read_until_udp(int sockfd, char *buffer, size_t max_len, char delimiter, int timeout_sec) {
//    #define BUF_SIZE 256
//    static char internal_buf[BUF_SIZE];
//    static size_t buf_pos = 0;
//    static size_t buf_len = 0;
//    size_t out_pos = 0;
//    bool packet_complete = false;
//
//    struct timeval tv;
//    tv.tv_sec = timeout_sec;
//    tv.tv_usec = 0;
//    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
// //    while (out_pos < max_len - 1 && !packet_complete) {
//        if (buf_pos >= buf_len) {
//            buf_len = recvfrom(sockfd, internal_buf, BUF_SIZE, 0, NULL, NULL);
//            ESP_LOGI(TAG, "recvfrom(buf_len) = %d", buf_len);
//            if (buf_len == -1) {
//                ESP_LOGW(TAG, "recvfrom(buf_len) = %d", buf_len);
//                return -1;
//            }
//            else if (buf_len == 0)
//            {
//                ESP_LOGW(TAG, "recvfrom(buf_len) = %d", buf_len);
//                return 0;
//            }
//            buf_pos = 0;
//        }
//
//        char c = internal_buf[buf_pos++];
//        buffer[out_pos++] = c;
//
//        if (c == delimiter) {
//            packet_complete = true;
//        }
//    }
//
//    buffer[out_pos] = '\0';
//    return out_pos;
//}

void start_uart_server(void *pvParameters)
{
    int result = 1;
    int sockfd = 0;
    struct sockaddr_in serv_addr, cli_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    memset(&cli_addr,  0, sizeof(serv_addr));

    const size_t RECVBUFF_SIZE = 256;
    char recvBuff[RECVBUFF_SIZE];
    memset(&recvBuff, 0, RECVBUFF_SIZE);

    if((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
    {
        ESP_LOGE(TAG, "Could not create socket");
        result = 2;
        goto ERROR;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        ESP_LOGE(TAG, "Bind failed");
        result = 3;
        close(sockfd);
        goto ERROR;
    }

    ESP_LOGI(TAG, "UART server started on port %d", PORT);

    while(1) {
        //ssize_t n = read_until_udp(sockfd, recvBuff, RECVBUFF_SIZE, ';', 1);

        socklen_t addr_len = sizeof(cli_addr);
        ssize_t received = recvfrom(sockfd, recvBuff, RECVBUFF_SIZE - 1, 0,
                                  (struct sockaddr *)&cli_addr, &addr_len);
        if (received < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                ESP_LOGW(TAG, "Receive timeout");
            } else {
                ESP_LOGE(TAG, "recvfrom failed: errno %d", errno);
            }
            continue;
        }

        recvBuff[received] = '\0';

        char *semicolon = strchr(recvBuff, ';');
        if (!semicolon) {
            ESP_LOGW(TAG, "No semicolon found - ignoring packet");
            continue;
        }

        size_t response_len = semicolon - recvBuff + 1;

        char addr_str[INET_ADDRSTRLEN];
        inet_ntoa_r(cli_addr.sin_addr, addr_str, sizeof(addr_str));

        ESP_LOGI(TAG, "DATA len(%d) from %s:%d: %s", response_len, addr_str, ntohs(cli_addr.sin_port), recvBuff);
        if (uart_write_bytes(UART_NUM, recvBuff, response_len) <= 0)
        {
            ESP_LOGE(TAG, "Failed to send data over UART");
            result = errno;
            goto ERROR;
        }
    }

    result = 0;
    close(sockfd);
ERROR:
    ESP_LOGI(TAG, "Exit");
    return;
    //return result;
}
