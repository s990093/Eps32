#include "websocket_server.h"
Body WebSocketClient::body;

WebSocketClient::WebSocketClient(const char *ssid, const char *password)
    : ssid(ssid), password(password) {}

void WebSocketClient::onMessageCallback(WebsocketsMessage message)
{
    Serial.print("Got Message: ");
    Serial.println(message.data());

    // 创建一个静态 JSON 缓存对象
    StaticJsonDocument<200> doc;

    // 解析收到的 JSON 消息
    DeserializationError error = deserializeJson(doc, message.data());

    // 检查是否解析成功
    if (error)
    {
        Serial.print("deserializeJson() failed: ");
        Serial.println(error.f_str());
        return;
    }

    // 获取 JSON 数据中的字段
    const char *device = doc["device"];
    const char *state = doc["state"];

    currentDevice = String(device);
    currentState = String(state);
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
    String websocketConnectionString = String("ws://") + WEBSOCKET_SERVER;

    Serial.println(websocketConnectionString);

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

String WebSocketClient::getState()
{
    return currentDevice;
}

String WebSocketClient::getDevice()
{
    return currentState;
}

// @brief sned message
void WebSocketClient::sendMessage(double brightness)
{
    // Construct JSON message
    String jsonString = "{\"device\":\"";
    jsonString.concat(DEVICE_NAME);
    jsonString.concat("\",\"deivce\":\"send_brightness\",\"brightness\":");
    jsonString.concat(String(brightness));
    jsonString.concat("}");

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
