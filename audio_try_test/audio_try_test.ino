// 头文件
#include <driver/i2s.h>

//按照接线确定编号
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14

// 使用I2S处理器
#define I2S_PORT I2S_NUM_0

// 定义缓冲区长度
#define bufferLen 64
int16_t sBuffer[bufferLen];

// 定义阈值和计时变量
const float threshold = 50; // 设置阈值
unsigned long lastAboveThresholdTime = 0; // 上次超过阈值的时间
bool printEnabled = true; // 控制打印的开关

void i2s_install() {
  //设置I2S处理器配置
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 44100,
    .bits_per_sample = i2s_bits_per_sample_t(16),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = 0,
    .dma_buf_count = 8,
    .dma_buf_len = bufferLen,
    .use_apll = false
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
}

void i2s_setpin() {
  // 设置I2S引脚配置
  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,
    .ws_io_num = I2S_WS,
    .data_out_num = -1,
    .data_in_num = I2S_SD
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

void setup() {
  // 设置串口监视器
  Serial.begin(115200);
  Serial.println(" ");
  delay(1000);
  // 设置I2S
  i2s_install();
  i2s_setpin();
  i2s_start(I2S_PORT);
  delay(500);
}

void loop() {

  // 获取I2S数据并将其放入数据缓冲区
  size_t bytesIn = 0;
  esp_err_t result = i2s_read(I2S_PORT, &sBuffer, bufferLen, &bytesIn, portMAX_DELAY);

  if (result == ESP_OK)
  {
    // 读取I2S数据缓冲区
    int16_t samples_read = bytesIn / 8;
    if (samples_read > 0) {
      float mean = 0;
      for (int16_t i = 0; i < samples_read; ++i) {
        mean += (sBuffer[i]);
      }
      // 取数据读数的平均值
      mean /= samples_read;

      // 如果音频信号大于阈值，打印数值
      if (mean > threshold) {
        Serial.println("============samples_read");
        Serial.println(samples_read);
        Serial.println("============mean");
        Serial.println(mean);
        lastAboveThresholdTime = millis(); // 更新最后超过阈值的时间
        printEnabled = true; // 使能打印
      } else {
        // 如果连续三秒没有超过阈值，则停止打印
        if (millis() - lastAboveThresholdTime > 3000 && printEnabled) {
          Serial.println("Stopped printing due to no signal above threshold for 3 seconds");
          printEnabled = false; // 关闭打印  #结束完成后post信息，后端判断声音时间长度来决定立即返回还是翻译文本返回
        }
      }
    }
  }
}
