#include <Arduino.h>
#include "config.h"
#include "sensor.h"

// tcp/ip
#include "my_wifi.h"
#include "tcp_client.h"
#include "websocket_server.h"

// helper functions
#include "PrintHelper.h"

PrintHelper printHelper;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    printHelper.printHeader("System Setup");

    // setupWiFi();
    printHelper.printDebug("WiFi setup complete");

    // WebSocketClient webSocketClient("yourSSID", "yourPASSWORD");
    // webSocketClient.setup();
    // printHelper.printDebug("WebSocket client setup complete");

    setupSensor();
    printHelper.printDebug("Sensor setup complete");
}

void loop()
{
    // checkWiFiConnection();
    led_run();
}
