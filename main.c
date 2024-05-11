#include "esp_wifi.h"

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch (event->event_id) {
        case SYSTEM_EVENT_AP_START:
            ESP_LOGI(TAG, "Access Point started");
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:
            ESP_LOGI(TAG, "Station connected");
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(TAG, "Station disconnected");
            break;
        default:
            break;
    }
    return ESP_OK;
}

void setup() {
    Serial.begin(115200);

    const wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    esp_wifi_init(&wifi_init_config);
    tcpip_adapter_init();

    esp_event_loop_init(event_handler, NULL);

    char* ssid = "carplay_wap";
    char* pwrd = "carplay_wap";

    wifi_config_t wifi_config = {
        .ap = {
            .ssid = ssid,
            .password = pwrd,
            .max_connection = 4,
            .authmode = WIFI_AUTH_WPA_WPA2_PSK
        }
    };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);

    esp_wifi_start();

    Serial.println("esp32 wifi access point");
}

void loop() {
}
