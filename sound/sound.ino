#include "driver/i2s.h"
#include "soc/i2s_reg.h"
//
//#define BUFLEN 256
//
//static const i2s_port_t i2s_num = I2S_NUM_0; // i2s port number
//
//static const i2s_config_t i2s_config = {
//     .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
//     .sample_rate = 22050,
//     .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
//     .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
//     .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
//     .intr_alloc_flags = 0, // default interrupt priority
//     .dma_buf_count = 8,
//     .dma_buf_len = 64,
//     .use_apll = false
//};
//
//static const i2s_pin_config_t pin_config = {
//    .bck_io_num = 26,
//    .ws_io_num = 25,
//    .data_out_num = I2S_PIN_NO_CHANGE,
//    .data_in_num = 22
//};
//
//void setup() { 
//   pinMode(22, INPUT);
//   i2s_driver_install(i2s_num, &i2s_config, 0, NULL);   //install and start i2s driver
//   REG_SET_BIT(  I2S_TIMING_REG(i2s_num),BIT(9));   /*  #include "soc/i2s_reg.h"   I2S_NUM -> 0 or 1*/
//   REG_SET_BIT( I2S_CONF_REG(i2s_num), I2S_RX_MSB_SHIFT);
//   i2s_set_pin(i2s_num, &pin_config);
//}
//
//int32_t audio_buf[BUFLEN];
//
//void loop() {
//    // int bytes_read = i2s_read(i2s_num, audio_buf, sizeof(audio_buf), 0);
//    // have fun with your data
//}



#include <WiFi.h>
#include <HTTPClient.h>


const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here
const char* serverUrl = "http://192.168.43.185:5000/audio"; // 更改为你的服务器URL

const int i2sBckPin = 26;
const int i2sDataPin = 25;
const int i2sLrckPin = 27;

void connectToWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();

  // 配置I2S接口
  i2s_config_t i2sConfig = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_RIGHT,
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S_MSB | I2S_COMM_FORMAT_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 8,
    .dma_buf_len = 64
  };

  i2s_pin_config_t pinConfig = {
      .bck_io_num = 26,   // Serial Clock (SCK)
      .ws_io_num = 25,    // Word Select (WS)
      .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
      .data_in_num = 33   // Serial Data (SD)
  };

  i2s_driver_install(I2S_NUM_0, &i2sConfig, 0, NULL);
  i2s_set_pin(I2S_NUM_0, &pinConfig);

  // 启动I2S接收
  i2s_start(I2S_NUM_0);
}


void loop() {
  WiFiClient client;

  // 创建HTTP请求
  HTTPClient http;
  http.begin(client, serverUrl);
  http.addHeader("Content-Type", "application/octet-stream");

  const size_t bufferSize = 1024;
  byte buffer[bufferSize];

  Serial.println("Recording...");
  size_t bytesRead = 0;
  size_t totalBytesRead = 0;

  // 读取I2S数据并发送到服务器
  while (totalBytesRead < bufferSize) {
    bytesRead = 0;
    i2s_read(I2S_NUM_0, buffer, bufferSize, &bytesRead, portMAX_DELAY);
    totalBytesRead += bytesRead;
    Serial.println(totalBytesRead);
    Serial.println(bytesRead);
    
    
    http.POST(reinterpret_cast<uint8_t*>(buffer), bytesRead);
  }

  http.end();

  Serial.println("Recording sent");

  delay(3000); // 每隔5秒发送一次录音
}
