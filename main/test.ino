#include <Arduino.h>
#include <WiFi.h>
#include "config.h"

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // 連接到 WiFi
    connectToWiFi();

    // 在 Serial 監視器輸出一些訊息
    Serial.println("Test.ino started.");
    Serial.print("Connected to WiFi network: ");
    Serial.println(WIFI_SSID);
}

void loop()
{
    // 在這裡可以加入其他的測試邏輯或演示程式碼
    delay(1000);
}

void connectToWiFi()
{
    Serial.println();
    Serial.printf("Connecting to WiFi network: %s\n", WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    Serial.println();
    Serial.println("WiFi connected.");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}
