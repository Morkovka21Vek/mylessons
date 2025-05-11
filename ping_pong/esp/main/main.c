#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <esp_log.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "esp_netif.h"
#include "protocol_examples_common.h"
#include "protocol_examples_utils.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"

#include <esp_system.h>
#include "nvs_flash.h"
#include "esp_eth.h"

#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_mac.h"
#include "sdkconfig.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "esp_timer.h"
#include "esp_wifi.h"

#include "wifi.h"

#define EXAMPLE_HTTP_QUERY_KEY_MAX_LEN  (64)

static const char *TAG = "MorkoServ";

static int button_count1 = 0;
static int button_count2 = 0;

static volatile uint32_t last_interrupt_time1 = 0;
static volatile uint32_t last_interrupt_time2 = 0;

#include "pages.h"

static httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    ESP_LOGD(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        ESP_LOGD(TAG, "Registering URI handlers");
        for(int i = 0; i < sizeof(pages_list)/sizeof(httpd_uri_t); i++)
          httpd_register_uri_handler(server, &pages_list[i]);
        return server;
    }

    ESP_LOGD(TAG, "Error starting server!");
    return NULL;
}

void IRAM_ATTR button_tick1(void* arg) {
  uint32_t current_time = esp_timer_get_time() / 1000;
  if (current_time - last_interrupt_time1 > 100) {
    button_count1++;
    last_interrupt_time1 = current_time;
  }
}
void IRAM_ATTR button_tick2(void* arg) {
  uint32_t current_time = esp_timer_get_time() / 1000;
  if (current_time - last_interrupt_time2 > 100) {
    button_count2++;
    last_interrupt_time2 = current_time;
  }
}

static esp_err_t stop_webserver(httpd_handle_t server)
{
    return httpd_stop(server);
}

static void disconnect_handler(void* arg, esp_event_base_t event_base,
                               int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGD(TAG, "Stopping webserver");
        if (stop_webserver(*server) == ESP_OK) {
            *server = NULL;
        } else {
            ESP_LOGE(TAG, "Failed to stop http server");
        }
    }
}

static void connect_handler(void* arg, esp_event_base_t event_base,
                            int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGD(TAG, "Starting webserver");
        *server = start_webserver();
    }
}

void app_main(void)
{
    gpio_set_direction(CONFIG_DOWN_GPIO_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_DOWN_GPIO_NUM, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(CONFIG_DOWN_GPIO_NUM, GPIO_INTR_NEGEDGE);

    gpio_set_direction(CONFIG_UP_GPIO_NUM, GPIO_MODE_INPUT);
    gpio_set_pull_mode(CONFIG_UP_GPIO_NUM, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(CONFIG_UP_GPIO_NUM, GPIO_INTR_NEGEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(CONFIG_DOWN_GPIO_NUM, button_tick1, NULL);
    gpio_isr_handler_add(CONFIG_UP_GPIO_NUM, button_tick2, NULL);

    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    wifi_init_softap();

    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

    server = start_webserver();

    while (server) {
        sleep(5);
    }
}

