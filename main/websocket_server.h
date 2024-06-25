#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <ArduinoWebsockets.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "config.h"

using namespace websockets;

class Body
{
public:
    String type;
    String content;

    bool fromJson(const String &jsonString);
};

class WebSocketClient
{
public:
    WebSocketClient(const char *ssid, const char *password);
    // 存储接收到的设备和状态信息
    static String currentDevice;
    static String currentState;
    void setup();
    void loop();
    String getDevice() const;
    String getState() const;

    void sendMessage(double brightness);

private:
    const char *ssid;
    const char *password;

    WebsocketsClient client;

    static void onMessageCallback(WebsocketsMessage message);
    static void onEventsCallback(WebsocketsEvent event, String data);
    void connectWebSocket();

    static Body body;
};

// void webSocketEvent_v2(WStype_t type, const uint8_t *payload, size_t length);

#endif // WEBSOCKET_SERVER_H
