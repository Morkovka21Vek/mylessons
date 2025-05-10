static esp_err_t home_get_handler(httpd_req_t *req)
{
    httpd_resp_send(req, mainPage, HTTPD_RESP_USE_STRLEN);

    if (httpd_req_get_hdr_value_len(req, "Host") == 0) {
        ESP_LOGD(TAG, "Request headers lost");
    }
    return ESP_OK;
}

static const httpd_uri_t home_page = {
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
