#include <Arduino.h>
#include "config.h"
#include "PrintHelper.h"
#include "WebSocketTasks.h"

PrintHelper printHelper(DEBUG_MODE);
MymyWebSocketClient myWebSocketClient(WIFI_SSID, WIFI_PASSWORD);

bool continueBreathing = CONTINUE_BREATHING; // Global variable visible across the file

TaskHandle_t websocketTaskHandle;

void websocketTask(void *parameter);

void setup()
{
    printHelper.printHeader("System Setup");

    setCpuFrequencyMhz(CpuFrequencyMhz);
    Serial.begin(SERIAL_BAUD_RATE);
    setupWiFi(printHelper);
    setupSensor(printHelper);

    xTaskCreatePinnedToCore(
        websocketTask,
        "WebSocket Task",
        10000, NULL,
        10,
        &websocketTaskHandle,
        CORE_0); // Core 0

    xTaskCreatePinnedToCore(
        heartbeat,          // Task function
        "Heartbeat Task",   // Task name
        10000,              // Stack size (bytes)
        &continueBreathing, // Task parameter (passing address of continueBreathing)
        0,                  // Priority (0 is the lowest priority)
        NULL,               // Task handle (optional)
        CORE_1              // Core to run the task on
    );
}

void loop()
{
    // Empty loop as FreeRTOS is handling the tasks
}

void websocketTask(void *parameter)
{
    myWebSocketClient.setup(printHelper);
    for (;;)
    {
        myWebSocketClient.loop();
        // myWebSocketClient.getDevice();
        // Check if there is an issue with myWebSocketClient
        // if (!myWebSocketClient.isConnected())
        // {
        //     continueBreathing = false; // Stop breathing if WebSocket client is not connected
        //     break;                     // Exit the loop
        // }
        vTaskDelay(1); // Yield to other tasks
    }
}