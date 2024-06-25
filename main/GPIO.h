#ifndef GPIO_H
#define GPIO_H

void setupSensor();
int readSensor();
bool buttonPressed(int pin);
void heartbeat();

//
void led_run();
void sg90();
void song();
#endif
