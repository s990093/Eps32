#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>

extern WiFiClient client; // 使用 extern 關鍵字來聲明變量

void setupWiFi();
void checkWiFiConnection();

#endif // WIFI_H
