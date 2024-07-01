#ifndef CAMERA_STREAMER_H
#define CAMERA_STREAMER_H

#include <WiFi.h>
#include "esp_camera.h"
#include "esp_timer.h"
#include "img_converters.h"
#include "fb_gfx.h"
#include "fd_forward.h"
#include "fr_forward.h"
#include "rtsp_server.h"

class CameraStreamer
{
public:
    CameraStreamer(const char *ssid, const char *password)
        : ssid(ssid), password(password) {}

    void begin()
    {
        connectWiFi();
        initCamera();
        rtsp_server.begin();
    }

    void handle()
    {
        rtsp_server.handle();
    }

private:
    const char *ssid;
    const char *password;

    void connectWiFi()
    {
        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.println("Connecting to WiFi...");
        }
        Serial.println("Connected to WiFi");
    }

    void initCamera()
    {
        camera_config_t config;
        config.ledc_channel = LEDC_CHANNEL_0;
        config.ledc_timer = LEDC_TIMER_0;
        config.pin_d0 = 5;
        config.pin_d1 = 18;
        config.pin_d2 = 19;
        config.pin_d3 = 21;
        config.pin_d4 = 36;
        config.pin_d5 = 39;
        config.pin_d6 = 34;
        config.pin_d7 = 35;
        config.pin_xclk = 0;
        config.pin_pclk = 22;
        config.pin_vsync = 25;
        config.pin_href = 23;
        config.pin_sccb_sda = 26;
        config.pin_sccb_scl = 27;
        config.pin_pwdn = 32;
        config.pin_reset = -1;
        config.xclk_freq_hz = 20000000;
        config.pixel_format = PIXFORMAT_JPEG;

        if (psramFound())
        {
            config.frame_size = FRAMESIZE_VGA;
            config.jpeg_quality = 10;
            config.fb_count = 2;
        }
        else
        {
            config.frame_size = FRAMESIZE_QVGA;
            config.jpeg_quality = 12;
            config.fb_count = 1;
        }

        esp_err_t err = esp_camera_init(&config);
        if (err != ESP_OK)
        {
            Serial.printf("Camera init failed with error 0x%x", err);
            return;
        }
    }
};

#endif // CAMERA_STREAMER_H
