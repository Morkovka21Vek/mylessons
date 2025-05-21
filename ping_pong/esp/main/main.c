#include "esp_event.h"
#include "esp_netif.h"
#include "nvs_flash.h"

#include "gpio.h"
#include "server.h"
#include "wifi.h"

void app_main(void) {
    nvs_flash_init();
    esp_netif_init();
    esp_event_loop_create_default();

    init_gpio();
    wifi_init_softap();

    start_webserver();
}
