#include "websocket_server.h"

Body WebSocketClient::body;

WebSocketClient::WebSocketClient(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

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

// @brief sned message
void WebSocketClient::sendMessage(const String &type, const String &content)
{
    // Construct JSON message
    String jsonString = "{\"type\":\"" + type + "\",\"content\":\"" + content + "\"}";

    // Send message via WebSocket if connected
    if (client.available())
    {
        client.send(jsonString);
    }
    else
    {
        Serial.println("WebSocket is not connected.");
    }
}

bool Body::fromJson(const String &jsonString)
{
    // Assuming jsonString is something like '{"type":"example", "content":"Hello World"}'
    int startIndex = jsonString.indexOf('{');
    int endIndex = jsonString.lastIndexOf('}');
    if (startIndex == -1 || endIndex == -1 || endIndex <= startIndex)
    {
        return false; // JSON format error
    }

    // Extract content from jsonString
    String content = jsonString.substring(startIndex + 1, endIndex);

    // Find type field
    int typeIndex = content.indexOf("\"type\":");
    if (typeIndex == -1)
    {
        return false; // type field not found
    }
    int typeValueStartIndex = content.indexOf('"', typeIndex + 7) + 1; // Skip past "type":
    int typeValueEndIndex = content.indexOf('"', typeValueStartIndex);
    if (typeValueStartIndex == -1 || typeValueEndIndex == -1)
    {
        return false; // type field value not found
    }
    String typeValue = content.substring(typeValueStartIndex, typeValueEndIndex);

    // Find content field
    int contentIndex = content.indexOf("\"content\":");
    if (contentIndex == -1)
    {
        return false; // content field not found
    }
    int contentValueStartIndex = content.indexOf('"', contentIndex + 10) + 1; // Skip past "content":
    int contentValueEndIndex = content.indexOf('"', contentValueStartIndex);
    if (contentValueStartIndex == -1 || contentValueEndIndex == -1)
    {
        return false; // content field value not found
    }
    String contentValue = content.substring(contentValueStartIndex, contentValueEndIndex);

    // Assign extracted values to class members
    type = typeValue;
    content = contentValue;

    return true;
}