#include "esp_camera.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_timer.h"
#include "driver/uart.h"
#include "uart.h"
#include <errno.h>

#define TAG "SERVER.c"

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    httpd_req_t *req;
    size_t len;
} jpg_chunking_t;

esp_err_t setboundaries_httpd_handler(httpd_req_t *req) {
    int result = -1;
    const size_t CONTENT_BUF_SIZE = 7;
    char content[CONTENT_BUF_SIZE];

    const size_t UART_BUF_SIZE = CONTENT_BUF_SIZE+4;
    char uart_buf[UART_BUF_SIZE];

    const size_t RXBUFSIZE = 10;
    char rx_buf[RXBUFSIZE];

    int ret = httpd_req_recv(req, content, MIN(req->content_len, CONTENT_BUF_SIZE));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            ESP_LOGW(TAG, "408");
            httpd_resp_send_408(req);
        }
        goto ERROR;
    }

    snprintf(uart_buf, UART_BUF_SIZE, "&3)%s;", content);

    if (uart_write_bytes(UART_NUM, uart_buf, UART_BUF_SIZE) <= 0) {
        ESP_LOGW(TAG, "Failed to send data over UART");
        httpd_resp_set_status(req, "500 UART write");
        httpd_resp_send(req, NULL, 0);
        result = errno;
        goto ERROR;
    }

    if(uart_read_line(UART_NUM, rx_buf, RXBUFSIZE, 1000, ';') == -1) {
        if (errno == ETIMEDOUT) {
            ESP_LOGW(TAG, "Timeout read data over UART");
            result = ETIMEDOUT;
            httpd_resp_set_status(req, "504 UART Timeout");
            httpd_resp_send(req, NULL, 0);
        } else {
            ESP_LOGW(TAG, "Failed to read data over UART");
            result = -2;
            httpd_resp_set_status(req, "500 UART read");
            httpd_resp_send(req, NULL, 0);
        }
        goto ERROR;
    }

    int status;
    sscanf(rx_buf, "&3)%d", &status);
    httpd_resp_set_status(req,
            (status==200) ? HTTPD_200 : "503 change the jumper");

    httpd_resp_send(req, NULL, 0);
    result = ESP_OK;
ERROR:
    return result;
}

esp_err_t absoluteturn_httpd_handler(httpd_req_t *req) {
    int result = -1;
    const size_t CONTENT_BUF_SIZE = 3;
    char content[CONTENT_BUF_SIZE];

    const size_t UART_BUF_SIZE = CONTENT_BUF_SIZE+4;
    char uart_buf[UART_BUF_SIZE];

    int ret = httpd_req_recv(req, content, MIN(req->content_len, CONTENT_BUF_SIZE));
    if (ret <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            ESP_LOGW(TAG, "408");
            httpd_resp_send_408(req);
        }
        goto ERROR;
    }
    snprintf(uart_buf, UART_BUF_SIZE, "&2)%s;", content);

    if (uart_write_bytes(UART_NUM, uart_buf, UART_BUF_SIZE) <= 0) {
        ESP_LOGW(TAG, "Failed to send data over UART");
        httpd_resp_set_status(req, "500 UART write");
        httpd_resp_send(req, NULL, 0);
        result = errno;
        goto ERROR;
    }

    httpd_resp_send(req, NULL, 0);
    result = ESP_OK;
ERROR:
    return result;
}
esp_err_t getstatus_httpd_handler(httpd_req_t *req) {
    const size_t BUF_SIZE = 100;
    char resp_json[BUF_SIZE];

    const size_t RXBUFSIZE = 20;
    char rx_buf[RXBUFSIZE];

    int result = -1;

    const char* uart_body = "&4);";
    if (uart_write_bytes(UART_NUM, uart_body, strlen(uart_body)) <= 0) {
        ESP_LOGW(TAG, "Failed to send data over UART");
        result = errno;
        httpd_resp_set_status(req, "500 UART write");
        httpd_resp_send(req, NULL, 0);
        goto ERROR;
    }

    if(uart_read_line(UART_NUM, rx_buf, RXBUFSIZE, 1000, ';') == -1) {
        if (errno == ETIMEDOUT) {
            ESP_LOGW(TAG, "Timeout read data over UART");
            result = ETIMEDOUT;
            httpd_resp_set_status(req, "504 UART Timeout");
            httpd_resp_send(req, NULL, 0);
        } else {
            ESP_LOGW(TAG, "Failed to read data over UART");
            result = -2;
            httpd_resp_set_status(req, "500 UART read");
            httpd_resp_send(req, NULL, 0);
        }
        goto ERROR;
    }

    float pct, vol;
    sscanf(rx_buf, "&1)%f,%f", &pct, &vol);

    snprintf(resp_json, BUF_SIZE,
        "{"
        "\"battery\": {"
        "\"pct\": %f,"
        "\"vol\": %f"
        "}"
        "}",
        pct, vol);

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    result = ESP_OK;
ERROR:
    return result;
}
esp_err_t getsettings_httpd_handler(httpd_req_t *req) {
    const size_t BUF_SIZE = 100;
    char resp_json[BUF_SIZE];

    const size_t RXBUFSIZE = 20;
    char rx_buf[RXBUFSIZE];

    int result = -1;

    const char* uart_body = "&1);";
    if (uart_write_bytes(UART_NUM, uart_body, strlen(uart_body)) <= 0) {
        ESP_LOGW(TAG, "Failed to send data over UART");
        result = errno;
        httpd_resp_set_status(req, "500 UART write");
        httpd_resp_send(req, NULL, 0);
        goto ERROR;
    }

    if(uart_read_line(UART_NUM, rx_buf, RXBUFSIZE, 1000, ';') == -1) {
        if (errno == ETIMEDOUT) {
            ESP_LOGW(TAG, "Timeout read data over UART");
            result = ETIMEDOUT;
            httpd_resp_set_status(req, "504 UART Timeout");
            httpd_resp_send(req, NULL, 0);
        } else {
            ESP_LOGW(TAG, "Failed to read data over UART");
            result = -2;
            httpd_resp_set_status(req, "500 UART read");
            httpd_resp_send(req, NULL, 0);
        }
        goto ERROR;
    }

    int baudrate, logs, reverse, servo;
    sscanf(rx_buf, "&1)%d,%d,%d,%d", &baudrate, &logs, &reverse, &servo);

    snprintf(resp_json, BUF_SIZE,
        "{"
        "\"baudrate\": %s,"
        "\"logs\": %s,"
        "\"reverse\": %s,"
        "\"servo\": %s"
        "}",
        baudrate?"true":"false",
        logs    ?"true":"false",
        reverse ?"true":"false",
        servo   ?"true":"false");

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    result = ESP_OK;
ERROR:
    return result;
}

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

        httpd_uri_t getsettings_uri = {
            .uri       = "/api/getsettings",
            .method    = HTTP_GET,
            .handler   = getsettings_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &getsettings_uri);

        httpd_uri_t absoluteturn_uri = {
            .uri       = "/api/servo/absoluteturn",
            .method    = HTTP_POST,
            .handler   = absoluteturn_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &absoluteturn_uri);

        httpd_uri_t setboundaries_uri = {
            .uri       = "/api/servo/setboundaries",
            .method    = HTTP_POST,
            .handler   = setboundaries_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &setboundaries_uri);

        httpd_uri_t getstatus_uri = {
            .uri       = "/api/getstatus",
            .method    = HTTP_GET,
            .handler   = getstatus_httpd_handler,
            .user_ctx  = NULL
        };
        httpd_register_uri_handler(server, &getstatus_uri);
    }
}
