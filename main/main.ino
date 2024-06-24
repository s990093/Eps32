#include <Arduino.h>
#include "config.h"
#include "my_wifi.h"
#include "sensor.h"
#include "tcp_client.h"
#include "websocket_server.h"
#include "PrintHelper.h"

PrintHelper printHelper;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    printHelper.printHeader("System Setup");

    setupWiFi();
    printHelper.printDebug("WiFi setup complete");

    // WebSocketClient webSocketClient("yourSSID", "yourPASSWORD");
    // webSocketClient.setup();
    // printHelper.printDebug("WebSocket client setup complete");

    setupSensor();
    printHelper.printDebug("Sensor setup complete");
}

void loop()
{
    checkWiFiConnection();

    // 模擬感測器數據讀取
    int sensorData = readSensor();

    delay(BASE_DELAY); // 每隔1秒更新一次感測器數據
}
