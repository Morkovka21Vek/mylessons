#include <unistd.h>
#include "esp_http_server.h"
#include "esp_event.h"
#include "esp_netif.h"
#include <esp_system.h>
#include "nvs_flash.h"

#include "wifi.h"
#include "server.h"
#include "gpio.h"

void app_main(void)
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    init_gpio();
    wifi_init_softap();

    httpd_handle_t server = start_webserver();

    while (server) {
        sleep(5);
    }
}
