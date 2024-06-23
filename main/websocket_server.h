#ifndef WEBSOCKET_SERVER_H
#define WEBSOCKET_SERVER_H

#include <ArduinoWebsockets.h> // Include necessary library
#include "config.h"            // Include your configuration file

extern websocket::WebsocketsClient webSocket; // Declare an external variable

void initWebSocket(); // Declare function prototypes
void startWebSocketServer();
void webSocketEvent(WStype_t type, uint8_t *payload, size_t length);

#endif // WEBSOCKET_SERVER_H
