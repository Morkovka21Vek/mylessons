static esp_err_t api_v1__get_buttons_status_handler(httpd_req_t *req)
{
    char resp_json[100];

    snprintf(resp_json, sizeof(resp_json), "{\n  \"btn1\": %d,\n  \"btn2\": %d\n}", 
        !gpio_get_level(but_left_down_pin), 
        !gpio_get_level(but_left_up_pin));

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t api_v1__get_buttons_status = {
    .uri       = "/api/v1/get_buttons_status",
    .method    = HTTP_GET,
    .handler   = api_v1__get_buttons_status_handler,
};

static esp_err_t api_v1__get_buttons_count_handler(httpd_req_t *req)
{
    char resp_json[100];

    snprintf(resp_json, sizeof(resp_json), "%d;%d", 
        button_count1, 
        button_count2);
    
    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t api_v1__get_buttons_count = {
    .uri       = "/api/v1/get_buttons_count",
    .method    = HTTP_GET,
    .handler   = api_v1__get_buttons_count_handler,
};

