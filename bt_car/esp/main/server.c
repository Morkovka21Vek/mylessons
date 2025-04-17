#include "esp_camera.h"
#include "esp_log.h"
#include "esp_http_server.h"
#include "esp_timer.h"

#define TAG "SERVER.c"

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
