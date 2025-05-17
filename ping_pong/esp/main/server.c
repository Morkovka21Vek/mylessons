#include "esp_log.h"
#include "esp_http_server.h"
#include "gpio.h"

#define BUF_SIZE 50

static const char *TAG = "server";

static esp_err_t get_buttons_status_handler(httpd_req_t *req)
{
    char response[BUF_SIZE];

    snprintf(response, BUF_SIZE, "{\"btn1\": %s,\"btn2\": %s}",
        getButton_level(0)?"true":"false",
        getButton_level(1)?"true":"false");

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);

    return httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
}

static const httpd_uri_t get_buttons_status_uri = {
    .uri       = "/get_buttons_status",
    .method    = HTTP_GET,
    .handler   = get_buttons_status_handler,
};

static esp_err_t get_buttons_count_handler(httpd_req_t *req)
{
    char response[BUF_SIZE];

    snprintf(response, BUF_SIZE, "%d;%d",
        getButton_count(0),
        getButton_count(1));

    httpd_resp_set_type(req, HTTPD_TYPE_TEXT);

    return httpd_resp_send(req, response, HTTPD_RESP_USE_STRLEN);
}

static const httpd_uri_t get_buttons_count_uri = {
    .uri       = "/get_buttons_count",
    .method    = HTTP_GET,
    .handler   = get_buttons_count_handler,
};

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);

    if (httpd_start(&server, &config) == ESP_OK) {
        httpd_register_uri_handler(server, &get_buttons_status_uri);
        httpd_register_uri_handler(server, &get_buttons_count_uri);
        return server;
    }

    ESP_LOGE(TAG, "Error start server!");
    return NULL;
}
