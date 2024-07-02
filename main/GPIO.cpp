#include "GPIO.h"
#include "PrintHelper.h"
int speakerPin = 9;

const int NUM_STRAPPING_PINS = sizeof(STRAPPING_PINS) / sizeof(STRAPPING_PINS[0]);
const int NUM_SPI_FLASH_PINS = sizeof(SPI_FLASH_PINS) / sizeof(SPI_FLASH_PINS[0]);
const int NUM_INPUT_ONLY_PINS = sizeof(INPUT_ONLY_PINS) / sizeof(INPUT_ONLY_PINS[0]);

void setupSensor(PrintHelper printHelper)
{

    pinMode(Debug_LED, OUTPUT);
    pinMode(OUTPUT_SIGNAL_ARDUINO, OUTPUT);
    pinMode(OUTPUT_SIGNAL_ESP32, OUTPUT);

    digitalWrite(OUTPUT_SIGNAL_ARDUINO, LOW);
    digitalWrite(OUTPUT_SIGNAL_ESP32, LOW);

    // for (long i = 0; i < duration * 1000L; i += tone * 2)
    // {
    //     digitalWrite(speakerPin, HIGH);
    //     delayMicroseconds(tone);
    //     digitalWrite(speakerPin, LOW);
    //     delayMicroseconds(tone);
    // }
    //   pinMode(speakerPin, OUTPUT);

    /*


    check


    */
    // 检查是否使用不建议使用的引脚
    // for (int i = 0; i < NUM_STRAPPING_PINS; i++)
    // {
    //     if (pinMode(STRAPPING_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using strapping pin GPIO %d\n", STRAPPING_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }

    // for (int i = 0; i < NUM_SPI_FLASH_PINS; i++)
    // {
    //     if (pinMode(SPI_FLASH_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using SPI flash pin GPIO %d\n", SPI_FLASH_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }

    // for (int i = 0; i < NUM_INPUT_ONLY_PINS; i++)
    // {
    //     if (pinMode(INPUT_ONLY_PINS[i]) != INPUT)
    //     {
    //         Serial.printf("Error: Using input-only pin GPIO %d\n", INPUT_ONLY_PINS[i]);
    //         while (true)
    //             ; // 停止程序
    //     }
    // }
    printHelper.printDebug("Sensor setup complete");
}

void heartbeat(void *parameter)

{
    bool *continueBreathingPtr = (bool *)parameter; // Cast parameter to bool pointer

    static bool state = false;
    static uint8_t brightness = 0;
    static int8_t fadeAmount = 5;

    for (;;)
    {
        if (*continueBreathingPtr) // Dereference the pointer to check the value
        {
            analogWrite(Debug_LED, brightness);

            brightness = brightness + fadeAmount;

            if (brightness <= 0 || brightness >= 255)
            {
                fadeAmount = -fadeAmount;
            }

            vTaskDelay(pdMS_TO_TICKS(50)); // Adjust the delay as needed for the breathing effect
        }
        else
        {
            digitalWrite(Debug_LED, LED_OFF); // Ensure LED is off when breathing is stopped
            vTaskDelay(pdMS_TO_TICKS(100));   // Delay to conserve CPU resources
        }
    }
}
