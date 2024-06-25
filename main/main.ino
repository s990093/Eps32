#include <Arduino.h>
#include "config.h"
#include "GPIO.h"
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
    // printHelper.printDebug("Job added to scheduler");
    Serial.begin(SERIAL_BAUD_RATE);
    printHelper.printHeader("System Setup");

    setupWiFi();
    printHelper.printDebug("WiFi setup complete");

    webSocketClient.setup();
    printHelper.printDebug("WebSocket client setup complete");

    setupSensor();

    printHelper.printDebug("Sensor setup complete");

    // 初始化定时器
    timer = timerBegin(TIMER_NUMBER, TIMER_PRESCALER, TIMER_COUNT_UP);
    // 绑定中断服务函数
    timerAttachInterrupt(timer, &onTimer, true);
    // 配置定时器中断间隔
    timerAlarmWrite(timer, TIMER_INTERVAL_MICROS, true);
    // 启用定时器中断
    timerAlarmEnable(timer);

    // scheduler.addJob(&heartbeat, 1000);
}

void loop()
{
    // 主循环中不需要做任何事
    // sg90();
    webSocketClient.loop();

    // sendGetRequest("/test/");

    // webSocketClient.sendMessage(200.2);
}
