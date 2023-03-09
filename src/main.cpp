#include "Secrets.h"
#include <Arduino.h>
#include <ArduinoHA.h>
#include <WiFi.h>

#include "globals.h"
#include "ha_wrappers.h"
#include "pin.h"
#include "ui.h"

byte mac[] = {0x00, 0x10, 0xFA, 0x6E, 0x38, 0x5A};

WiFiClient wifi;
HADevice device(mac, sizeof(mac));
HAMqtt mqtt(wifi, device);

TaskHandle_t UiTaskHandle{};

void mqtt_thread(void *param)
{
    for (;;)
    {
        mqtt.loop();
        delay(5);
    }
}

void setup()
{
    Serial.begin(115200);
    while (!Serial)
    {
    }

    devices::init_devices();
    UI::init();

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_NAME, WIFI_PASSWORD);
    UI::wifi_start();
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.println(WiFi.status());
        delay(1000);
    }
    UI::wifi_connected();

    device.setName("Rice cooker");
    device.setSoftwareVersion("1.0.0");

    mqtt.begin(IPAddress(MQTT_IP), 1883, MQTT_USER, MQTT_PASS);

    xTaskCreatePinnedToCore(mqtt_thread, "MQTT Thread", 10000, NULL, 0, &UiTaskHandle, 0);
}

void loop()
{
    UI::draw(app_state);
    app_state.tick();
}