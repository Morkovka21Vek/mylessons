#include "esp_camera.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define OneMHz 1000000
uint8_t xclkMhz = 20;

#define UART_NUM UART_NUM_1
#define TX_PIN 13
#define RX_PIN 15

#define TAG "CAMERA"

// Определение GPIO-пинов для ESP32-CAM
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// Настройки Wi-Fi точки доступа
#define WIFI_SSID      "ESP32-CAM"
#define WIFI_PASSWORD  "12345678"
#define WIFI_CHANNEL   1
#define MAX_STA_CONN   4

// chunking
typedef struct {
    httpd_req_t *req;
    size_t len;
} jpg_chunking_t;

static size_t jpg_encode_stream(void * arg, size_t index, const void* data, size_t len){
    jpg_chunking_t *j = (jpg_chunking_t *)arg;
    if(!index){
        j->len = 0;
    }
    if(httpd_resp_send_chunk(j->req, (const char *)data, len) != ESP_OK){
        return 0;
    }
    j->len += len;
    return len;
}

esp_err_t jpg_httpd_handler(httpd_req_t *req){
    camera_fb_t * fb = NULL;
    esp_err_t res = ESP_OK;
    size_t fb_len = 0;
    int64_t fr_start = esp_timer_get_time();

    fb = esp_camera_fb_get();
    if (!fb) {
        ESP_LOGE(TAG, "Camera capture failed");
        httpd_resp_send_500(req);
        return ESP_FAIL;
    }
    res = httpd_resp_set_type(req, "image/jpeg");
    if(res == ESP_OK){
        res = httpd_resp_set_hdr(req, "Content-Disposition", "inline; filename=capture.jpg");
    }

    if(res == ESP_OK){
        if(fb->format == PIXFORMAT_JPEG){
            fb_len = fb->len;
            res = httpd_resp_send(req, (const char *)fb->buf, fb->len);
        } else {
            jpg_chunking_t jchunk = {req, 0};
            res = frame2jpg_cb(fb, 80, jpg_encode_stream, &jchunk)?ESP_OK:ESP_FAIL;
            httpd_resp_send_chunk(req, NULL, 0);
            fb_len = jchunk.len;
        }
    }
    esp_camera_fb_return(fb);
    int64_t fr_end = esp_timer_get_time();
    ESP_LOGI(TAG, "JPG: %zuKB %" PRId64 "ms", fb_len / 1024, (fr_end - fr_start) / 1000);
    return res;
}

esp_err_t mjpeg_httpd_handler(httpd_req_t *req) {
    camera_fb_t *fb = NULL;
    esp_err_t res = ESP_OK;
    char part_buf[64];

    res = httpd_resp_set_type(req, "multipart/x-mixed-replace; boundary=boundary");
    if (res != ESP_OK) {
        return res;
    }

    while (true) {
        fb = esp_camera_fb_get();
        if (!fb) {
            ESP_LOGE(TAG, "Camera capture failed");
            res = ESP_FAIL;
            break;
        }

        int part_len = sprintf(part_buf, "\r\n--boundary\r\nContent-Type: image/jpeg\r\nContent-Length: %d\r\n\r\n", fb->len);

        if (httpd_resp_send_chunk(req, part_buf, part_len) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to send frame header");
            esp_camera_fb_return(fb);
            break;
        }

        if (httpd_resp_send_chunk(req, (const char *)fb->buf, fb->len) != ESP_OK) {
            ESP_LOGE(TAG, "Failed to send frame data");
            esp_camera_fb_return(fb);
            break;
        }

        esp_camera_fb_return(fb);

        vTaskDelay(33 / portTICK_PERIOD_MS);  // ~30 FPS (1000ms / 30 = 33ms)
    }

    httpd_resp_send_chunk(req, "\r\n--boundary--\r\n", 14);
    return res;
}

// Инициализация камеры
void init_camera() {
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_1;
    config.ledc_timer = LEDC_TIMER_1;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = xclkMhz * OneMHz;
    config.pixel_format = PIXFORMAT_JPEG;
    config.grab_mode = CAMERA_GRAB_LATEST;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.sccb_i2c_port = 0;// using I2C 0. to be sure what port we are using.

    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Camera init failed with error 0x%x", err);
        return;
    }
}

// Инициализация NVS
void init_nvs() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

// Настройка Wi-Fi точки доступа
void init_wifi_ap() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASSWORD,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .channel = WIFI_CHANNEL
        },
    };

    if (strlen(WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi AP started. SSID: %s, Password: %s, Channel: %d", WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
}

// Инициализация UART
void init_uart() {
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };

    uart_driver_install(UART_NUM, 1024, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    uart_set_pin(UART_NUM, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

// Настройка и запуск HTTP-сервера
void start_webserver() {
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_uri_t jpg_uri = {
            .uri       = "/jpg",
            .method    = HTTP_GET,
            .handler   = jpg_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &jpg_uri);

        httpd_uri_t mjpeg_uri = {
            .uri       = "/stream",
            .method    = HTTP_GET,
            .handler   = mjpeg_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &mjpeg_uri);
    }
}

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

void app_main() {
    init_nvs();
    init_uart();
    init_camera();
    init_wifi_ap();
    start_webserver();

    xTaskCreate(start_uart_server, "uart_server_task", 4096, NULL, configMAX_PRIORITIES - 2, NULL);
}
