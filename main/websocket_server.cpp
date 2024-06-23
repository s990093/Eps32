#include "websocket_server.h"
#include <ArduinoJson.h> // 引入 ArduinoJson 库

/*
    Secured Esp32 Websockets Client

    This sketch:
        1. Connects to a WiFi network
        2. Connects to a Websockets server (using WSS)
        3. Sends the websockets server a message ("Hello Server")
        4. Sends the websocket server a "ping"
        5. Prints all incoming messages while the connection is open

    NOTE:
    The sketch dosen't check or indicate about errors while connecting to
    WiFi or to the websockets server. For full example you might want
    to try the example named "Esp32-Client" (And use the ssl methods).

    Hardware:
        For this sketch you only need an Esp32 board.

    Created 15/02/2019
    By Gil Maimon
    https://github.com/gilmaimon/ArduinoWebsockets

*/

// 定义输入 JSON 的结构体
struct InputJSON
{
    String command;
    int param1;
    float param2;
};

// 定义输出 JSON 的结构体
struct OutputJSON
{
    String status;
    int data;
};

/// @brief Initializes the WebSocket connection.
void initWebSocket()
{
    webSocket.begin(websocket_server, WEBSOCKET_PORT, WEBSOCKET_SERVER);
    webSocket.onEvent(webSocketEvent);
    webSocket.setReconnectInterval(WEBSOCKET_TIMEOUT); // 尝试重新连接的时间间隔
    Serial.println("WebSocket connecting...");
}

void webSocketEvent(WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.println("WebSocket Disconnected");
        break;
    case WStype_CONNECTED:
        Serial.println("WebSocket Connected");
        // 连接后发送一条消息
        webSocket.sendTXT("Hello Server");
        break;
    case WStype_TEXT:
        Serial.printf("Received text: %s\n", payload);

        // 解析收到的 JSON 数据
        StaticJsonDocument<200> jsonBuffer; // 定义 JSON 缓冲区
        DeserializationError error = deserializeJson(jsonBuffer, payload, length);

        // 检查解析是否成功
        if (error)
        {
            Serial.print("deserializeJson() failed: ");
            Serial.println(error.c_str());
            return;
        }

        // 解析输入 JSON
        InputJSON input;
        input.command = jsonBuffer["command"].as<String>();
        input.param1 = jsonBuffer["param1"].as<int>();
        input.param2 = jsonBuffer["param2"].as<float>();

        // 在此处根据收到的指令执行相应的操作
        if (input.command == "command1")
        {
            // 执行命令1的操作，可以根据参数 input.param1 和 input.param2 进行处理
            Serial.println("Received command1");
        }
        else if (input.command == "command2")
        {
            // 执行命令2的操作
            Serial.println("Received command2");
        }
        else
        {
            // 未知命令
            Serial.println("Unknown command");
        }

        // 示例：构建并发送输出 JSON
        OutputJSON output;
        output.status = "OK";
        output.data = 123;

        // 序列化输出 JSON
        char outputBuffer[128];
        serializeJson(output, outputBuffer);

        // 发送输出 JSON 到 WebSocket
        webSocket.sendTXT(outputBuffer);

        break;
    }
}

/// @brief Handles WebSocket events such as connection, disconnection, and received messages.
void startWebSocketServer()
{
    webSocket.loop();
}