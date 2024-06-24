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

    void setup();
    void loop();

private:
    const char *ssid;
    const char *password;
    WebsocketsClient client;

    static void onMessageCallback(WebsocketsMessage message);
    static void onEventsCallback(WebsocketsEvent event, String data);

    static Body body;
};

#endif // WEBSOCKET_SERVER_H
