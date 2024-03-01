#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>
#include <Arduino.h>
#include <driver/i2s.h>

// WiFi网络设置
const char* ssid = "HUAWEI P50 Pro";
const char* password = "12345678";



//##################################################################


#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"



// Randomly picked URL
const char *URL="http://192.168.43.185:5000/audio/mp3";

AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2SNoDAC *out;

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2)-1]=0;
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
  Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
  if (code != 257 && code != 565 && code != 260) {

  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
  }
}


void initURLaudio(){

  audioLogger = &Serial;
  file = new AudioFileSourceICYStream(URL);
  file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(file, 1024*2);
  buff->RegisterStatusCB(StatusCallback, (void*)"buffer");
  out = new AudioOutputI2SNoDAC();
  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
  mp3->begin(buff, out);
  }
  
/////////////////////////////////////////////////////////////


void loopURLaudio() {
  static int lastms = 0;

  if (mp3->isRunning()) {
    if (millis()-lastms > 1000) {
      lastms = millis();
      //Serial.printf("Running for %d ms...\n", lastms);
      Serial.flush();
     }
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}


//##################################################################
// Flask服务器设置
const char* serverAddress = "http://192.168.43.185:5000/record";

// INMP441麦克风设置
#define SAMPLE_RATE     (16000)
#define SAMPLE_SIZE     (2048)  // 减小采样大小以减少延迟

// 音频数据缓冲区
uint8_t sample_buffer[SAMPLE_SIZE];
//按照接线确定编号
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14
// 使用I2S处理器
#define I2S_PORT I2S_NUM_0
//#####################################################################
void setup() {
  Serial.begin(115200);

  // 初始化WiFi连接
  connectToWiFi();

  
  

  //////
  

  

  // 开始采集音频并发送到服务器
  //collectAndSendAudio();
}
int click_push_count = 0;
int click_once_count = 0;
int array [] ={0,0,0,0,0,0};
bool click();
void collectAndSendAudio();
void loop() {

  
  
  if(click()){
      click_push_count = click_push_count+1;
      if (click_push_count==2){ //短按
        click_once_count +=1;
        }
//      if (click_push_count==1000){//长按
//        click_once_count -=2;
//        }
       Serial.println(click_push_count); 
    }

    
  else{
      click_push_count = 1;

      if (click_once_count==0){
           
        
          if (array[0]==-2){
          array[0]=1;
          array[1]=0;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;
          
          initURLaudio();
          delay(1000); // 等待一秒钟
          Serial.println("0"); }
          loopURLaudio();

        
        
        }      
      if (click_once_count==1){
          if (array[1]==0){
          array[0]=0;
          array[1]=1;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;
          // 初始化I2S总线
          initI2S();
          delay(1000); // 等待一秒钟
          Serial.println("1"); }
        
        collectAndSendAudio();
 
        }
      if (click_once_count==2){
        click_once_count = 0;
          if (array[2]==0){
          array[0]=0;
          array[1]=2;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;
          Serial.println("2"); }
       
        }

        
      }


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

void initI2S() {
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
}

void collectAndSendAudio() {
  //while(true) {
    size_t bytesIn = 0;
    esp_err_t result = i2s_read(I2S_PORT, sample_buffer, SAMPLE_SIZE, &bytesIn, portMAX_DELAY);
    if (result == ESP_OK) {
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
  //}
}


bool click(){

   const int touchPin = 4; // 使用 T0 获取数据
   const int threshold = 40;
   // variable for storing the touch pin value 
   int touchValue;
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  //Serial.print(touchValue);
  //Serial.print("\n");

  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    //digitalWrite(ledPin, HIGH);
     //Serial.println("有触控，灯亮");
    return true;
  }
  else{
    // turn LED off
    //digitalWrite(ledPin, LOW);
    //Serial.println(" - LED off");
    return false;
  }
  //delay(500);  
  }
