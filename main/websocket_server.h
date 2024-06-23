#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <AsyncWebSocket.h>

extern AsyncWebSocket ws;

void onWsEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);

#endif // WEBSOCKET_SERVER_H
