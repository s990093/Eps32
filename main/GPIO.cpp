#include "GPIO.h"
#include <Arduino.h>
#include <ESP32Servo.h>
#include "config.h"

const int buttonPin = 0; // 按钮连接的引脚
const int servoPin = 7;  // 伺服电机连接的引脚
Servo myServo;
int buzzerPin = 25;

void setupSensor()
{
    pinMode(buzzerPin, OUTPUT);

    pinMode(SENSOR_PIN, INPUT);
    pinMode(Debug_LED, OUTPUT);

    // sg90
    pinMode(buttonPin, INPUT_PULLUP); // 使用内部上拉电阻
    myServo.attach(servoPin);
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
        digitalWrite(LED_ARRAY_PINS[i], LED_ON); // Turn LED on
        delay(LED_DELAY_TIME);
        digitalWrite(LED_ARRAY_PINS[i], LED_OFF); // Turn LED off
    }
}

void sg90()
{
    if (buttonPressed(buttonPin))
    {
        myServo.write(90); // 将伺服电机转动到90度
        Serial.println("Servo turned to 90 degrees!");
        delay(1000);      // 保持位置1秒
        myServo.write(0); // 返回到0度
        Serial.println("Servo returned to 0 degrees!");
        delay(1000); // 保持位置1秒
    }
}

bool buttonPressed(int pin)
{
    static int lastButtonState = HIGH;         // 上一次的按钮状态
    static unsigned long lastDebounceTime = 0; // 上次按下的时间
    unsigned long debounceDelay = 10;          // 延迟时间（毫秒）

    int reading = digitalRead(pin); // 读取按钮状态

    // 如果按钮状态改变
    if (reading != lastButtonState)
    {
        lastDebounceTime = millis(); // 更新最后按下的时间
    }

    // Serial.print(lastDebounceTime);
    // Serial.print(". ");
    // Serial.println(millis());

    // 如果经过了延时时间
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
        // 检查按钮状态是否确实改变
        if (reading != lastButtonState)
        {
            lastButtonState = reading;

            // 如果按钮按下
            if (reading == LOW)
            {
                return true;
            }
        }
    }

    return false;
}

void song()
{

    int t = 300;
    tone(buzzerPin, 1319, t);     // E6
    tone(buzzerPin, 1047, t);     // C6
    tone(buzzerPin, 784, t);      // G5
    tone(buzzerPin, 1047, t);     // C6
    tone(buzzerPin, 1175, t);     // D6
    tone(buzzerPin, 1568, 2 * t); // G6
    tone(buzzerPin, 1175, t);     // D6
    tone(buzzerPin, 1319, t);     // E6
    tone(buzzerPin, 1175, t);     // D6
    tone(buzzerPin, 784, t);      // G5
    tone(buzzerPin, 1047, 2 * t); // C6
    tone(buzzerPin, 0, 5000);     // 休息3秒
}

void heartbeat()
{
    static bool state = 0;
    if (state == 0)
        state = 1;
    else
        state = 0;
    // Serial.println("heartbeat!");
    digitalWrite(Debug_LED, state);
}