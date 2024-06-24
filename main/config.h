#ifndef CONFIG_H
#define CONFIG_H

// Debug Configuration
/// @todo
#define DEBUG_MODE true // Enable or disable debug mode

// LED Configuration
#define LED_PIN 13 // Pin number for the LED
const int LED_ARRAY_PINS[] = {23, 22, 21};
#define LED_DELAY_TIME 100
#define NUM_LEDS 3

// Base Configuration
#define SERIAL_BAUD_RATE 115200 // Baud rate for serial communication
#define BASE_DELAY 1000         // Base delay in milliseconds

// WiFi Configuration
#define WIFI_SSID "your_wifi_ssid"         // Your WiFi SSID
#define WIFI_PASSWORD "your_wifi_password" // Your WiFi password

// Server Configuration
#define SERVER_ADDRESS "your_server_address" // Your server address
#define SERVER_PORT 8000                     // Your server port

// MQTT Configuration
#define MQTT_BROKER "your_mqtt_broker"                   // MQTT broker address
#define MQTT_PORT 1883                                   // MQTT broker port
#define MQTT_USER "your_mqtt_username"                   // MQTT username
#define MQTT_PASSWORD "your_mqtt_password"               // MQTT password
#define MQTT_TOPIC_SUBSCRIBE "your/mqtt/subscribe/topic" // MQTT subscription topic
#define MQTT_TOPIC_PUBLISH "your/mqtt/publish/topic"     // MQTT publish topic

// WebSocket Configuration
#define WEBSOCKET_SERVER "your.websocket.server" // WebSocket server address
#define WEBSOCKET_PORT 8000                      // WebSocket server port
#define WEBSOCKET_TIMEOUT 5000                   // WebSocket timeout in milliseconds

// Sensor Configuration
#define SENSOR_PIN 34             // Pin number for the sensor
#define SENSOR_TYPE "DHT22"       // Type of sensor (e.g., "DHT22", "DHT11")
#define SENSOR_READ_INTERVAL 2000 // Sensor read interval in milliseconds

// LED Configuration
#define LED_PIN 13     // Pin number for the LED
#define WIFI_OK_PIN 23 // Pin number for the LED
#define LED_ON HIGH    // LED on state
#define LED_OFF LOW    // LED off state

// Additional Configuration Parameters
#define DEVICE_NAME "your_device_name" // Name of your device
#define FIRMWARE_VERSION "1.0.0"       // Firmware version
#define HEARTBEAT_INTERVAL 60000       // Heartbeat interval in milliseconds
#define RECONNECT_INTERVAL 10000       // Reconnect interval in milliseconds

// API Configuration
#define API_KEY "your_api_key"           // API key for your service
#define API_ENDPOINT "your_api_endpoint" // API endpoint URL

// ㄖㄨㄟ
#define MAX_JOBS 10

#endif // CONFIG_H
