idf_component_register(SRCS "main.c" "camera.c" "wifi.c" "server.c" "fastserver.c" "uart.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp32-camera esp_http_server esp_wifi esp_timer nvs_flash)
