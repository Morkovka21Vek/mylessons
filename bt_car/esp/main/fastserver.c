#include "esp_log.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include "driver/uart.h"
#include "uart.h"

#define TAG "FASTSERVER.c"

//void uart_httpd_handler(int sockfd){
void uart_httpd_handler(void *pvParameters){
    int sockfd = (int)pvParameters;

    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    const char* body;
    const size_t RECVBUFF_SIZE = 256;
    char recvBuff[RECVBUFF_SIZE];
    memset(&recvBuff, 0, RECVBUFF_SIZE);

    int error_code = -1;

    while(1) {     //main while
        while(1) { //full req while
            ssize_t n = read(sockfd, recvBuff + strlen(recvBuff), RECVBUFF_SIZE - strlen(recvBuff) - 1);
            if (n == -1)
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK) {
                    vTaskDelay(10 / portTICK_PERIOD_MS);
                    continue;
                } else {
                    error_code = errno;
                    goto ERROR;
                }
            }
            else if (n == 0)
            {
                ESP_LOGI(TAG, "Client closed connection");
                goto CRITICAL_ERROR;
            }

            if (strstr(recvBuff, ";;") == NULL)
            {
                if (strlen(recvBuff) >= RECVBUFF_SIZE) {
                    ESP_LOGE(TAG, "Buffer overflow");
                    error_code = -2;
                    goto ERROR;
                }
                continue;
            }
            else
            {
                body = strstr(recvBuff, "\r\n\r\n");
                if(body == NULL)
                {
                    error_code = -3;
                    goto ERROR;
                }
                else
                {
                    body += 4;
                    ESP_LOGI(TAG, "DATA: %s", body);
                    if (uart_write_bytes(UART_NUM, body, strlen(body)) <= 0)
                    {
                        ESP_LOGW(TAG, "Failed to send data over UART");
                        error_code = errno;
                        goto ERROR;
                    }

                    const char* OK_RESP = "HTTP/1.1 200 OK\r\n\r\n";
                    write(sockfd, OK_RESP, strlen(OK_RESP));
                    break;
                }
            }
        }
        memset(recvBuff, 0, RECVBUFF_SIZE);
        continue;
ERROR:
        ESP_LOGW(TAG, "Code: %d", error_code);

        char FAIL_RESP_BUFF[50];
        snprintf(FAIL_RESP_BUFF, 50, "HTTP/1.1 500 INTERNAL SERVER ERROR(%d)\r\n\r\n", error_code);

        write(sockfd, FAIL_RESP_BUFF, strlen(FAIL_RESP_BUFF));
        memset(recvBuff, 0, RECVBUFF_SIZE);
        goto EXIT;
    }

EXIT:
    vTaskDelete(NULL);
    return;

CRITICAL_ERROR:
    close(sockfd);
    goto EXIT;
}

void start_uart_server(void *pvParameters)
{
    int result = 1;
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    if((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        ESP_LOGE(TAG, "Could not create socket");
        result = 2;
        goto ERROR;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(81);

    if (bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        ESP_LOGE(TAG, "Bind failed");
        result = 3;
        close(listenfd);
        goto ERROR;
    }

    if (listen(listenfd, 10) < 0) {
        ESP_LOGE(TAG, "Listen failed");
        result = 4;
        close(listenfd);
        goto ERROR;
    }

    ESP_LOGI(TAG, "UART server started on port 81");

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);
        if (connfd < 0) {
            ESP_LOGE(TAG, "Accept failed");
            continue;
        }

        xTaskCreate(uart_httpd_handler, "uart_handler_task", 4096, (void*)connfd, configMAX_PRIORITIES - 1, NULL);

        //uart_httpd_handler(connfd);
        sleep(1);
    }

    result = 0;
    close(listenfd);
ERROR:
    return;
    //return result;
}
