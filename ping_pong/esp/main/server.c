#include "esp_log.h"
#include "esp_http_server.h"
#include "gpio.h"

static const char *TAG = "server";

static esp_err_t get_buttons_status_handler(httpd_req_t *req)
{
    char resp_json[30];

    snprintf(resp_json, sizeof(resp_json), "{\"btn1\": %s,\"btn2\": %s}",
        getButton_level1()?"true":"false",
        getButton_level2()?"true":"false");

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static esp_err_t get_buttons_count_handler(httpd_req_t *req)
{
    char resp_json[20];

    snprintf(resp_json, sizeof(resp_json), "%d;%d",
        getButton_count1(),
        getButton_count2());

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    ESP_LOGD(TAG, "Starting server on port: '%d'", config.server_port);

    if (httpd_start(&server, &config) == ESP_OK) {
        static const httpd_uri_t get_buttons_status_uri = {
            .uri       = "/get_buttons_status",
            .method    = HTTP_GET,
            .handler   = get_buttons_status_handler,
        };
        httpd_register_uri_handler(server, &get_buttons_status_uri);

        static const httpd_uri_t get_buttons_count_uri = {
            .uri       = "/get_buttons_count",
            .method    = HTTP_GET,
            .handler   = get_buttons_count_handler,
        };
        httpd_register_uri_handler(server, &get_buttons_count_uri);

        return server;
    }

    ESP_LOGD(TAG, "Error starting server!");
    return NULL;
}
