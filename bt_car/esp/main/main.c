#include "camera.h"
#include "server.h"
#include "wifi.h"
#include "uart.h"
#include "fastserver.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "ESP-CAMERA"

// Инициализация NVS
void init_nvs() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}

void app_main() {
    init_nvs();
    init_uart();
    init_camera();
    init_wifi_ap();
    start_webserver();

    xTaskCreate(start_uart_server, "uart_server_task", 4096, NULL, configMAX_PRIORITIES - 2, NULL);
}
