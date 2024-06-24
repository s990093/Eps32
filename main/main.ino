#include <Arduino.h>
#include "config.h"
#include "sensor.h"
#include "tcp_client.h"
#include "websocket_server.h"
#include "PrintHelper.h"
#include "jobScheduler.h"

PrintHelper printHelper;
Scheduler scheduler;
WebSocketClient webSocketClient(WIFI_SSID, WIFI_PASSWORD);

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer()
{
    portENTER_CRITICAL_ISR(&timerMux);
    scheduler.run();
    portEXIT_CRITICAL_ISR(&timerMux);
}

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    printHelper.printHeader("System Setup");

    printHelper.printDebug("WiFi setup complete");
    printHelper.printDebug("WebSocket client setup complete");

    setupSensor();

    printHelper.printDebug("Sensor setup complete");

    timer = timerBegin(0, 80, true);             // Timer 0, prescaler 80, count up
    timerAttachInterrupt(timer, &onTimer, true); // Attach ISR
    timerAlarmWrite(timer, 500000, true);        // 0.5 second interval
    timerAlarmEnable(timer);                     // Enable timer interrupt

    // Example jobs
    scheduler.addJob(&readSensor, 1000); // Every 1 second

    printHelper.printDebug("Job added to scheduler");
}

void loop()
{
    // 主循环中不需要做任何事

    led_run();
}
