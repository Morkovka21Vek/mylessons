static esp_err_t api_get_status_buttons_get_handler(httpd_req_t *req)
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

static const httpd_uri_t api_get_status_buttons_struct = {
    .uri       = "/api/get_buttons_status",
    .method    = HTTP_GET,
    .handler   = api_get_status_buttons_get_handler,
};

static esp_err_t api_get_count_buttons_get_handler(httpd_req_t *req)
{
    char resp_json[100];

    snprintf(resp_json, sizeof(resp_json), "%d;%d", 
        button_count1, 
        button_count2);
    
    //button_count1 = button_count2 = 0;

    httpd_resp_set_type(req, HTTPD_TYPE_JSON);
    httpd_resp_send(req, resp_json, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t api_get_count_buttons_struct = {
    .uri       = "/api/get_buttons_count",
    .method    = HTTP_GET,
    .handler   = api_get_count_buttons_get_handler,
};

static esp_err_t home_get_handler(httpd_req_t *req)
{
    httpd_resp_send(req, mainPage, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t home_struct = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = home_get_handler,
};

esp_err_t http_404_error_handler(httpd_req_t *req, httpd_err_code_t err)
{
    /* For any other URI send 404 and close socket */
    httpd_resp_send_err(req, HTTPD_404_NOT_FOUND, "Some 404 error message");
    return ESP_FAIL;
}
