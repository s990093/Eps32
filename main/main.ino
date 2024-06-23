#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include "wifi.h"
#include "websocket_server.h"
#include "sensor.h"

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

void setup()
{
    Serial.begin(115200);
    setupWiFi();

    // 設定 WebSocket 路由
    ws.onEvent(onWsEvent);
    server.addHandler(&ws);

    // 初始化 GPIO 32

    server.begin();
    Serial.println("Server started");
}

void loop()
{
    checkWiFiConnection();
    // 模擬感測器數據讀取
    int sensorData = readSensor();

    // 將感測器數據轉換為 JSON 格式
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["event"] = "sensor_data";
    jsonDoc["data"] = sensorData;

    // 將 JSON 格式的數據轉換為字串
    String jsonStr;
    serializeJson(jsonDoc, jsonStr);

    // 廣播 JSON 格式的數據給所有 WebSocket 客戶端
    ws.textAll(jsonStr);

    // 檢查 WebSocket 事件
    ws.cleanupClients();

    delay(1000); // 每隔1秒更新一次感測器數據
}
