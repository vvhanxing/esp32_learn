#include <Arduino.h>

#if defined(ARDUINO_ARCH_RP2040)
void setup() {}
void loop() {}

#else
#if defined(ESP32)
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"
#include <driver/i2s.h>
#define I2S_PORT I2S_NUM_0;
// To run, set your ESP8266 build to 160MHz, update the SSID info, and upload.

// Enter your WiFi setup here:
#ifndef STASSID
#define STASSID "HUAWEI P50 Pro";  // Enter your SSID here
#define STAPSK  "12345678";  //Enter your Password here

#endif

const char* ssid = STASSID;
const char* password = STAPSK;

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
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}

void initmp3(){


   i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX ),
    .sample_rate =  44100,              // The format of the signal using ADC_BUILT_IN
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT, // is fixed at 12bit, stereo, MSB
    .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S_MSB,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,
    .dma_buf_len = 8,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
   };
   i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
//   i2s_set_adc_mode(ADC_UNIT_1, ADC1_CHANNEL_4);
//   i2s_adc_enable(I2S_NUM_0);

//  
// // 初始化I2S
//  i2s_config_t i2s_config = {
//    .mode = (i2s_mode_t)(I2S_MODE_MASTER |  I2S_MODE_TX ), // 加上 I2S_MODE_TX
//    .sample_rate = 44100,
//    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
//    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,   // 单声道
//    .communication_format = (i2s_comm_format_t) (I2S_COMM_FORMAT_STAND_I2S), // 修改通信格式
//    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
//    .dma_buf_count = 8,
//    .dma_buf_len = 256,
//     .fixed_mclk =false,
////    .use_apll = true, // Audio PLL is needed for low clock jitter
////    .tx_desc_auto_clear = true, // Silence on underflow
////    .fixed_mclk = 0, // Unused    
//    
//  
//     .mclk_multiple = I2S_MCLK_MULTIPLE_256,
//     .bits_per_chan = I2S_BITS_PER_CHAN_DEFAULT
//    
//    
//  };
//  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);
//  int port = 22;
//  i2s_set_pin((i2s_port_t)port, NULL);
//  
  audioLogger = &Serial;
  file = new AudioFileSourceICYStream(URL);
  file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(file, 2048);
  buff->RegisterStatusCB(StatusCallback, (void*)"buffer");
  out = new AudioOutputI2SNoDAC();
//  out->begin();
  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
  mp3->begin(buff, out);  
  
  }

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi");

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);

  // Try forever
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(1000);
  }
  Serial.println("Connected");
  
  initmp3();


}

void loopmp3(){

  static int lastms = 0;

  if (mp3->isRunning()) {
    if (millis()-lastms > 1000) {
      lastms = millis();
      Serial.printf("Running for %d ms...\n", lastms);
      Serial.flush();
     }
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    
    delay(1000);
  }
  
  }

void loop()
{
  loopmp3();

}
#endif
