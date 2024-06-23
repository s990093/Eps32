#include <Arduino.h>
#include "config.h"
#include "sensor.h"

void setupSensor()
{
    pinMode(SENSOR_PIN, INPUT);
}

int readSensor()
{
    return analogRead(SENSOR_PIN);
}
