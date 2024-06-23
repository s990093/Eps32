#include <Arduino.h>
#include "my_wifi.h"
#include "sensor.h"
#include "tcp_client.h"
#include "websocket_server.h"

void setup()
{
    Serial.begin(115200);

    setupWiFi();

    // 設定 WebSocket 路由
    initWebSocket();

    setupSensor();
}

void loop()
{
    // checkWiFiConnection();
    startWebSocketServer();

    // 模擬感測器數據讀取
    int sensorData = readSensor();

    delay(1000); // 每隔1秒更新一次感測器數據
}
