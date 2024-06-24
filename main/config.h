#ifndef CONFIG_H
#define CONFIG_H

// Debug Configuration
/// @todo
#define DEBUG_MODE true // Enable or disable debug mode

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
#define LED_PIN 13  // Pin number for the LED
#define LED_ON HIGH // LED on state
#define LED_OFF LOW // LED off state

// Additional Configuration Parameters
#define DEVICE_NAME "your_device_name" // Name of your device
#define FIRMWARE_VERSION "1.0.0"       // Firmware version
#define HEARTBEAT_INTERVAL 60000       // Heartbeat interval in milliseconds
#define RECONNECT_INTERVAL 10000       // Reconnect interval in milliseconds

// API Configuration
#define API_KEY "your_api_key"           // API key for your service
#define API_ENDPOINT "your_api_endpoint" // API endpoint URL

// This certificate was updated 15.04.2021, issues on Mar 15th 2021, expired on June 13th 2021
const char echo_org_ssl_ca_cert[] PROGMEM =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIEZTCCA02gAwIBAgIQQAF1BIMUpMghjISpDBbN3zANBgkqhkiG9w0BAQsFADA/\n"
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n"
    "DkRTVCBSb290IENBIFgzMB4XDTIwMTAwNzE5MjE0MFoXDTIxMDkyOTE5MjE0MFow\n"
    "MjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxCzAJBgNVBAMT\n"
    "AlIzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAuwIVKMz2oJTTDxLs\n"
    "jVWSw/iC8ZmmekKIp10mqrUrucVMsa+Oa/l1yKPXD0eUFFU1V4yeqKI5GfWCPEKp\n"
    "Tm71O8Mu243AsFzzWTjn7c9p8FoLG77AlCQlh/o3cbMT5xys4Zvv2+Q7RVJFlqnB\n"
    "U840yFLuta7tj95gcOKlVKu2bQ6XpUA0ayvTvGbrZjR8+muLj1cpmfgwF126cm/7\n"
    "gcWt0oZYPRfH5wm78Sv3htzB2nFd1EbjzK0lwYi8YGd1ZrPxGPeiXOZT/zqItkel\n"
    "/xMY6pgJdz+dU/nPAeX1pnAXFK9jpP+Zs5Od3FOnBv5IhR2haa4ldbsTzFID9e1R\n"
    "oYvbFQIDAQABo4IBaDCCAWQwEgYDVR0TAQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8E\n"
    "BAMCAYYwSwYIKwYBBQUHAQEEPzA9MDsGCCsGAQUFBzAChi9odHRwOi8vYXBwcy5p\n"
    "ZGVudHJ1c3QuY29tL3Jvb3RzL2RzdHJvb3RjYXgzLnA3YzAfBgNVHSMEGDAWgBTE\n"
    "p7Gkeyxx+tvhS5B1/8QVYIWJEDBUBgNVHSAETTBLMAgGBmeBDAECATA/BgsrBgEE\n"
    "AYLfEwEBATAwMC4GCCsGAQUFBwIBFiJodHRwOi8vY3BzLnJvb3QteDEubGV0c2Vu\n"
    "Y3J5cHQub3JnMDwGA1UdHwQ1MDMwMaAvoC2GK2h0dHA6Ly9jcmwuaWRlbnRydXN0\n"
    "LmNvbS9EU1RST09UQ0FYM0NSTC5jcmwwHQYDVR0OBBYEFBQusxe3WFbLrlAJQOYf\n"
    "r52LFMLGMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjANBgkqhkiG9w0B\n"
    "AQsFAAOCAQEA2UzgyfWEiDcx27sT4rP8i2tiEmxYt0l+PAK3qB8oYevO4C5z70kH\n"
    "ejWEHx2taPDY/laBL21/WKZuNTYQHHPD5b1tXgHXbnL7KqC401dk5VvCadTQsvd8\n"
    "S8MXjohyc9z9/G2948kLjmE6Flh9dDYrVYA9x2O+hEPGOaEOa1eePynBgPayvUfL\n"
    "qjBstzLhWVQLGAkXXmNs+5ZnPBxzDJOLxhF2JIbeQAcH5H0tZrUlo5ZYyOqA7s9p\n"
    "O5b85o3AM/OJ+CktFBQtfvBhcJVd9wvlwPsk+uyOy2HI7mNxKKgsBTt375teA2Tw\n"
    "UdHkhVNcsAKX1H7GNNLOEADksd86wuoXvg==\n"
    "-----END CERTIFICATE-----\n";

#endif // CONFIG_H
