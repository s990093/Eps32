#include <Arduino.h>
#include "config.h"
#include "sensor.h"

void setupSensor()
{
    pinMode(SENSOR_PIN, INPUT);

    // #ifdef DEBUG_MODE
    //     pinMode(, OUTPUT);
    // #endif

    for (int i = 0; i < NUM_LEDS; i++)
    {
        pinMode(LED_ARRAY_PINS[i], OUTPUT);
    }
}

int readSensor()
{
    return analogRead(SENSOR_PIN);
}

void led_run()
{

    for (int i = 0; i < NUM_LEDS; i++)
    {
        digitalWrite(LED_ARRAY_PINS[i], HIGH); // Turn LED on
        delay(LED_DELAY_TIME);
        digitalWrite(LED_ARRAY_PINS[i], LOW); // Turn LED off
    }
}
