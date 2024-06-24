#include "websocket_server.h"

Body WebSocketClient::body;

WebSocketClient::WebSocketClient(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

bool Body::fromJson(const String &jsonString)
{
    StaticJsonDocument<200> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    if (error)
    {
        return false;
    }
    type = doc["type"].as<String>();
    content = doc["content"].as<String>();
    return true;
}

void WebSocketClient::onMessageCallback(WebsocketsMessage message)
{
    Serial.print("Got Message: ");
    Serial.println(message.data());

    if (body.fromJson(message.data()))
    {
        Serial.print("Type: ");
        Serial.println(body.type);
        Serial.print("Content: ");
        Serial.println(body.content);
    }
    else
    {
        Serial.println("Failed to parse JSON");
    }
}

void WebSocketClient::onEventsCallback(WebsocketsEvent event, String data)
{
    if (event == WebsocketsEvent::ConnectionOpened)
    {
        Serial.println("Connection Opened");
    }
    else if (event == WebsocketsEvent::ConnectionClosed)
    {
        Serial.println("Connection Closed");
    }
    else if (event == WebsocketsEvent::GotPing)
    {
        Serial.println("Got a Ping!");
    }
    else if (event == WebsocketsEvent::GotPong)
    {
        Serial.println("Got a Pong!");
    }
}

void WebSocketClient::setup()
{
    Serial.begin(115200);
    // Connect to WiFi
    WiFi.begin(ssid, password);

    // Wait some time to connect to WiFi
    for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++)
    {
        Serial.print(".");
        delay(1000);
    }

    // Run callback when messages are received
    client.onMessage(onMessageCallback);

    // Run callback when events are occurring
    client.onEvent(onEventsCallback);

    // Build the WebSocket connection string
    String websocketConnectionString = String("ws://") + WEBSOCKET_SERVER + ":" + String(WEBSOCKET_PORT);

    // Connect to server
    client.connect(websocketConnectionString.c_str());

    // Send a message
    client.send("Hello Server");

    // Send a ping
    client.ping();
}

void WebSocketClient::loop()
{
    client.poll();
}
