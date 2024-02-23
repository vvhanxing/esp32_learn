#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <Wire.h>
#include <driver/i2s.h>

// WiFi网络设置
const char* ssid = "HUAWEI P50 Pro";
const char* password = "12345678";

// Flask服务器设置
const char* serverAddress = "http://192.168.43.185:5000/upload";

// INMP441麦克风设置
#define SAMPLE_RATE     (16000)
#define SAMPLE_TIME     (5)  // 采集时间，单位：秒
#define SAMPLE_SIZE     (SAMPLE_RATE * SAMPLE_TIME * sizeof(int8_t))

// 音频数据缓冲区
uint8_t sample_buffer[SAMPLE_SIZE];


//按照接线确定编号
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14
// 使用I2S处理器
#define I2S_PORT I2S_NUM_0

void setup() {
  Serial.begin(115200);

  // 初始化WiFi连接
  connectToWiFi();

  // 初始化I2S总线
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), // 接收模式
    .sample_rate = SAMPLE_RATE,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, // 只采集左声道
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 2,
    .dma_buf_len = 1024,
    .use_apll = false
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };
  
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);

  delay(1000); // 等待一秒钟

  // 开始采集音频
  collectAudio();
}

void loop() {
  // 不执行任何操作，采集音频只需执行一次
}

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
}

void collectAudio() {

  if (sample_buffer == NULL) {
    Serial.println("Failed to allocate memory for sample buffer");
    return;
  }
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, sample_buffer, SAMPLE_SIZE, &bytesIn,portMAX_DELAY);
  if (result == ESP_OK)
  {
    Serial.print("i2s_read result == ESP_OK");
    }
  // 创建HTTP客户端
  HTTPClient http;
  
  // 设置HTTP请求头
  http.begin(serverAddress);
    // 发送音频数据
  int httpResponseCode = http.POST(sample_buffer, SAMPLE_SIZE);

  // 检查HTTP响应
  if (httpResponseCode > 0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    String payload = http.getString();
    Serial.println(payload); // 打印服务器返回的内容
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  // 关闭HTTP连接
  http.end();

}
