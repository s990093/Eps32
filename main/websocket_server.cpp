#include "websocket_server.h"

// 静态成员初始化
Body WebSocketClient::body;
String WebSocketClient::currentDevice;
String WebSocketClient::currentState;

// WebSocket timeout in milliseconds
unsigned long lastPingTime = 0;
const unsigned long pingInterval = 10000;

unsigned long lastReconnectAttempt = 0;
const unsigned long reconnectDelay = 5000;

WebSocketClient::WebSocketClient(const char *ssid, const char *password)
    : ssid(ssid), password(password)
{
    // Constructor implementation
}

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

    // 更新当前设备和状态
    currentDevice = String(device);
    currentState = String(state);

    Serial.print("currentState -> ");
    Serial.println(currentState);

    if (currentState == STATE_PLAY)
    {
        digitalWrite(Debug_LED, LED_ON); // Turn LED on
    }
    else if (currentState == STATE_STOP)
    {
        digitalWrite(Debug_LED, LED_OFF); // Turn LED off
    }
    else if (currentState == STATE_ON)
    {
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_ON); // Turn ESP32 signal on
    }
    else if (currentState == STATE_OFF)
    {
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_OFF); // Turn ESP32 signal off
    }
    else
    {
        digitalWrite(Debug_LED, LED_OFF);           // Turn LED off (default action)
        digitalWrite(OUTPUT_SIGNAL_ESP32, LED_OFF); // Turn ESP32 signal off (default action)
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
        lastReconnectAttempt = millis(); // 记录断开连接的时间
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

    // Connect to WebSocket server
    connectWebSocket();
}

void WebSocketClient::loop()
{
    if (WiFi.status() != WL_CONNECTED)
    {
        // 尝试重新连接WiFi
        Serial.println("WiFi disconnected. Attempting to reconnect...");
        WiFi.reconnect();
        delay(1000);
    }

    if (!client.available() && millis() - lastReconnectAttempt > reconnectDelay)
    {
        // WebSocket断开连接且已经等待了足够长时间，尝试重新连接
        Serial.println("WebSocket disconnected. Attempting to reconnect...");
        connectWebSocket();
        lastReconnectAttempt = millis();
    }

    client.poll();

    // 发送ping消息作为心跳检测
    if (millis() - lastPingTime > pingInterval)
    {
        client.ping();
        lastPingTime = millis();
    }
}

void WebSocketClient::connectWebSocket()
{
    // Build the WebSocket connection string
    String websocketConnectionString = String("ws://") + WEBSOCKET_SERVER;

    Serial.println(websocketConnectionString);

    // Connect to server
    client.connect(websocketConnectionString.c_str());

    if (client.available())
    {
        // 连接成功后发送初始消息
        client.send("Hello Server");
    }
}

// 获取最新的设备信息
String WebSocketClient::getDevice() const
{
    return currentDevice;
}

// 获取最新的状态信息
String WebSocketClient::getState() const
{
    return currentState;
}

// @brief send message
void WebSocketClient::sendMessage(double brightness)
{
    // Check if WebSocket client is connected
    if (!client.available())
    {
        Serial.println("WebSocket is not connected.");
        return;
    }

    // Construct JSON message
    StaticJsonDocument<200> doc; // Adjust capacity as needed
    doc["device"] = DEVICE_NAME;
    doc["brightness"] = brightness;

    // Serialize JSON document to a String
    String jsonString;
    serializeJson(doc, jsonString);

    // Send message via WebSocket
    client.send(jsonString);
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
