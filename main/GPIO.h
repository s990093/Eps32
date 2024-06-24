#ifndef GPIO_H
#define GPIO_H

#include <Arduino.h>
#include "config.h"
#include "PrintHelper.h"

PrintHelper printHelper;

void setupSensor();
int readSensor();
void led_run();
#endif // SENSOR_H
