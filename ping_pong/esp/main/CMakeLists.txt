set(requires "")
idf_build_get_property(target IDF_TARGET)

if(${target} STREQUAL "linux")
    list(APPEND requires esp_stubs esp-tls esp_http_server protocol_examples_common nvs_flash)
endif()
idf_component_register(SRCS "main.c" "wifi.c" "server.c" "gpio.c"
                    INCLUDE_DIRS "."
                    REQUIRES ${requires})
