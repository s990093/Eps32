#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "esp_camera.h"

// Wi-Fi設定
const char* ssid = "eric home";    // Your WiFi SSID
const char* password = "12345677"; // Your WiFi password

// ESP32-CAM設定
#define CAMERA_MODEL_AI_THINKER // 選擇ESP32-CAM模組

// 手動設置相機引腳定義
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27
#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

// HTTP伺服器設定
AsyncWebServer server(80);

void setup() {
  // Serial通訊初始化
  Serial.begin(115200);
  
  // Wi-Fi連線A fatal error occurred: Failed to connect to ESP32: No serial data received.

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // 啟動相機
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // 初始化相機
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  // 設定HTTP伺服器路由
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><body><img src='/cam/stream'></body></html>";
    request->send(200, "text/html", html);
  });

  server.on("/cam/stream", HTTP_GET, [](AsyncWebServerRequest *request){
    camera_fb_t *fb = esp_camera_fb_get(); // Get the camera frame buffer
    if (!fb) {
      request->send(500); // Internal Server Error if no frame buffer available
      return;
    }

    request->send_P(200, "image/jpeg", fb->buf, fb->len);

    esp_camera_fb_return(fb); // Return the frame buffer
  });

  // 啟動HTTP伺服器
  server.begin();

  Serial.println("HTTP server started");
}

void loop() {
  // 放置你的其他程式碼，或者空白
}
