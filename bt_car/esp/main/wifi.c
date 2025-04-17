#include "esp_log.h"
#include "esp_wifi.h"
#include <string.h>

#define TAG "WIFI.c"

// Настройки Wi-Fi точки доступа
#define WIFI_SSID      "ESP32-CAM"
#define WIFI_PASSWORD  "12345678"
#define WIFI_CHANNEL   1
#define MAX_STA_CONN   15

// Настройка Wi-Fi точки доступа
void init_wifi_ap() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_ap();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = WIFI_SSID,
            .ssid_len = strlen(WIFI_SSID),
            .password = WIFI_PASSWORD,
            .max_connection = MAX_STA_CONN,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK,
            .channel = WIFI_CHANNEL
        },
    };

    if (strlen(WIFI_PASSWORD) == 0) {
        wifi_config.ap.authmode = WIFI_AUTH_OPEN;
    }

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "Wi-Fi AP started. SSID: %s, Password: %s, Channel: %d", WIFI_SSID, WIFI_PASSWORD, WIFI_CHANNEL);
}
