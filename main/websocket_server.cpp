#include "websocket_server.h"

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len)
{
    switch (type)
    {
    case WS_EVT_CONNECT:
        Serial.printf("WebSocket client #%u connected\n", client->id());
        break;
    case WS_EVT_DISCONNECT:
        Serial.printf("WebSocket client #%u disconnected\n", client->id());
        break;
    case WS_EVT_DATA:
        AwsFrameInfo *info = (AwsFrameInfo *)arg;
        if (info->opcode == WS_TEXT)
        {
            // 接收到文字訊息
            String msg = String((char *)data);
            Serial.printf("Received message from client #%u: %s\n", client->id(), msg.c_str());

            // 解析 JSON 訊息
            DynamicJsonBuffer jsonBuffer;
            JsonObject &root = jsonBuffer.parseObject(msg);

            // 檢查訊息類型並執行相應操作
            if (root.containsKey("event"))
            {
                String event = root["event"];
                if (event == "some_event")
                {
                    // 處理特定事件
                    // 例如，你可以在這裡做一些動作，如控制其他裝置或回應特定訊息
                }
            }
        }
        break;
    default:
        break;
    }
}