#include "esp_wifi.h"

static esp_err_t event_handler(void* ctx, system_event_t* event) {
    switch (event->event_id) {
        case SYSTEM_EVENT_AP_START:
            ESP_LOGI(TAG, "ap started");
            Serial.println("ap started");
            break;
        case SYSTEM_EVENT_AP_STACONNECTED:
            ESP_LOGI(TAG, "station connected");
            Serial.println("station connected");
            break;
        case SYSTEM_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(TAG, "station disconnected");
            Serial.println("station disconnected");
            break;
        default:
            break;
    }

    return ESP_OK;
}

void setup() {
    Serial.begin(115200);

    const wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

    unsigned char ssid[32] = "carplay_wap";
    unsigned char pwrd[64] = "carplay_wap";

    esp_wifi_init(&wifi_init_config);
    tcpip_adapter_init();

    esp_event_loop_init(event_handler, NULL);

    wifi_ap_config_t ap_config;

    memcpy(&ap_config.ssid, &ssid, 32);
    memcpy(&ap_config.password, &pwrd, 64);

    ap_config.max_connection = 4;
    ap_config.authmode = WIFI_AUTH_WPA_WPA2_PSK;

    wifi_config_t wifi_config = { .ap = ap_config };

    esp_wifi_set_mode(WIFI_MODE_AP);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);

    esp_wifi_start();

    Serial.println("esp32 wifi access point");
}

void loop() {
}
