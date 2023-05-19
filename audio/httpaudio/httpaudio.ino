#include <WiFi.h>
#include <WiFiClient.h>
#include <AudioFileSourceHTTPStream.h>
#include <AudioGeneratorMP3.h>

// WiFi网络凭据
const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password ="12345678";  //Enter your Password 

// 音频文件的URL
const char* audioUrl = "http://192.168.43.185:5000/audio/mp3";

// 定义音频生成器和文件源
AudioGeneratorMP3 audioGenerator;
AudioFileSourceHTTPStream *fileSource;

// 播放速度
float playSpeed = 1.0;

void setup() {
  Serial.begin(115200);

  // 连接WiFi网络
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // 初始化音频生成器
  audioGenerator.begin();

  // 创建HTTP音频文件源
  fileSource = new AudioFileSourceHTTPStream(audioUrl);
}

void loop() {
  if (audioGenerator.isRunning()) {
    // 音频正在播放，继续处理
    if (!audioGenerator.loop()) {
      // 播放结束
      audioGenerator.stop();
      fileSource->close();
      Serial.println("Playback finished");
    }
  } else {
    // 音频未播放，开始新的播放
    if (fileSource->open(audioUrl)) {
      // 成功打开音频文件
      Serial.println("Starting playback");
      audioGenerator.start(fileSource);
      audioGenerator.setSpeed(playSpeed); // 设置播放速度
    } else {
      // 无法打开音频文件
      Serial.println("Failed to open audio file");
    }
  }
}
