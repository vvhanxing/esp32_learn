#include <driver/i2s.h>
#include <SPIFFS.h>
#include <WiFi.h>
#define I2S_WS 15
#define I2S_SD 13
#define I2S_SCK 2
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE   (16000)
#define I2S_SAMPLE_BITS   (16)
#define I2S_READ_LEN      (16 * 1024)
#define RECORD_TIME       (10) //Seconds
#define I2S_CHANNEL_NUM   (1)
#define FLASH_RECORD_SIZE (I2S_CHANNEL_NUM * I2S_SAMPLE_RATE * I2S_SAMPLE_BITS / 8 * RECORD_TIME)

File file;
const char filename[] = "/recording.wav";
const int headerSize = 44; // wave header size



#define HTTP_TIMEOUT 10000
#define SERVER_HOST "192.168.43.185"
#define SERVER_PORT 5000

const char* ssid = "HUAWEI P50 Pro";
const char* password = "12345678";



void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");


  
  SPIFFSInit();
  i2sInit();
  xTaskCreate(i2s_adc, "i2s_adc", 1024 * 8, NULL, 1, NULL); // 根据需要修改堆栈深度，否则会无限重启....服了
}

void loop() {
  // put your main code here, to run repeatedly:

}

void SPIFFSInit() {
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFS initialisation failed!");
    while (1) yield();
  }

SPIFFS.remove("/audio_1257.wav"); // 移除掉已存在的file
SPIFFS.remove("/audio_1255.wav"); // 移除掉已存在的file

  SPIFFS.remove(filename); // 移除掉已存在的file
  file = SPIFFS.open(filename, FILE_WRITE);
  if (!file) {
    Serial.println("File is not available!");
  }

  byte header[headerSize];
  wavHeader(header, FLASH_RECORD_SIZE); // 生成wave header

  file.write(header, headerSize); // 写入header
  listSPIFFS();
}

void i2sInit() {
  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = I2S_SAMPLE_RATE,
    .bits_per_sample = i2s_bits_per_sample_t(I2S_SAMPLE_BITS),
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
    .intr_alloc_flags = 0,
    .dma_buf_count = 64,
    .dma_buf_len = 1024,  // 1024 samples per buffer
    .use_apll = 1         // use APLL-CLK,frequency 16MHZ-128MHZ,it's for audio
  };

  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);

  const i2s_pin_config_t pin_config = {
      .bck_io_num = 26,   // Serial Clock (SCK)
      .ws_io_num = 25,    // Word Select (WS)
      .data_out_num = I2S_PIN_NO_CHANGE, // not used (only for speakers)
      .data_in_num = 33   // Serial Data (SD)
  };

  i2s_set_pin(I2S_PORT, &pin_config);
}

// digital to analog：麦克风输入为digital code(binary)， 需要将编码转换成相应的电压值才能播放
void i2s_adc_data_scale(uint8_t * d_buff, uint8_t* s_buff, uint32_t len)
{
  uint32_t j = 0;
  uint32_t dac_value = 0;
  // 一个采样点是2byte，每2个byte
  for (int i = 0; i < len; i += 2) {
    dac_value = ((((uint16_t) (s_buff[i + 1] & 0xf) << 8) | ((s_buff[i + 0]))));
    d_buff[j++] = 0;
    d_buff[j++] = dac_value * 256 / 4096;
  }
}

// 录音任务
void i2s_adc(void *arg)
{
  int i2s_read_len = I2S_READ_LEN;
  // 已写入flash的大小
  int flash_wr_size = 0;
  // in i2s_read(),Number of bytes read, if timeout, bytes read will be less than the size passed in
  size_t bytes_read;
  // 每一次读取一个i2s_read_buff，大小：16 * 1024 bytes,DMA Buffer大小应该是其倍数，不然会报错：读取内存错误
  char* i2s_read_buff = (char*) calloc(i2s_read_len, sizeof(char));
  // 经过scale之后每次读取写入flash的buff
  uint8_t* flash_write_buff = (uint8_t*) calloc(i2s_read_len, sizeof(char));
  // 已经开始写入了，试试删掉，因为INMP441需要准备时间
  i2s_read(I2S_PORT, (void*) i2s_read_buff, i2s_read_len, &bytes_read, portMAX_DELAY);
  i2s_read(I2S_PORT, (void*) i2s_read_buff, i2s_read_len, &bytes_read, portMAX_DELAY);

  Serial.println(" *** Recording Start *** ");
  while (flash_wr_size < FLASH_RECORD_SIZE) {
    //read data from I2S bus, in this case, from ADC.
    i2s_read(I2S_PORT, (void*) i2s_read_buff, i2s_read_len, &bytes_read, portMAX_DELAY);
    // 展示一下都录了什么
    //example_disp_buf((uint8_t*) i2s_read_buff, 64);
    //save original data from I2S(ADC) into flash.
    // 先转换成电压值
    i2s_adc_data_scale(flash_write_buff, (uint8_t*)i2s_read_buff, i2s_read_len);
    file.write((const byte*) flash_write_buff, i2s_read_len);
    flash_wr_size += i2s_read_len;
    ets_printf("Sound recording %u%%\n", flash_wr_size * 100 / FLASH_RECORD_SIZE);
    ets_printf("Never Used Stack Size: %u\n", uxTaskGetStackHighWaterMark(NULL));
  }
  file.close();
  sendFileToServer();
  // 清空buff
  free(i2s_read_buff);
  i2s_read_buff = NULL;
  free(flash_write_buff);
  flash_write_buff = NULL;

  listSPIFFS();
  vTaskDelete(NULL);
}

// 展示buff内容的函数
void example_disp_buf(uint8_t* buf, int length)
{
  printf("======\n");
  for (int i = 0; i < length; i++) {
    printf("%02x ", buf[i]);
    if ((i + 1) % 8 == 0) {
      printf("\n");
    }
  }
  printf("======\n");
}
// 生成wav header，16bit 位深
void wavHeader(byte* header, int wavSize) { // 数字小端格式，字符大端格式
  header[0] = 'R';
  header[1] = 'I';
  header[2] = 'F';
  header[3] = 'F';
  unsigned int fileSize = wavSize + headerSize - 8;
  header[4] = (byte)(fileSize & 0xFF); // file size, 4byte integer
  header[5] = (byte)((fileSize >> 8) & 0xFF);
  header[6] = (byte)((fileSize >> 16) & 0xFF);
  header[7] = (byte)((fileSize >> 24) & 0xFF);
  header[8] = 'W';
  header[9] = 'A';
  header[10] = 'V';
  header[11] = 'E';
  header[12] = 'f';
  header[13] = 'm';
  header[14] = 't';
  header[15] = ' ';
  header[16] = 0x10; // length of format data = 16, 4byte integer
  header[17] = 0x00;
  header[18] = 0x00;
  header[19] = 0x00;
  header[20] = 0x01; // format type:1(PCM), 2byte integer
  header[21] = 0x00;
  header[22] = 0x01; // channel number:1, 2byte integer
  header[23] = 0x00;
  header[24] = 0x80; // sample rate:16000=0x00003E80, 4byte integer
  header[25] = 0x3E;
  header[26] = 0x00;
  header[27] = 0x00;
  header[28] = 0x00; // SampleRate*BitPerSample*ChannelNum/8=16000*16*1/8=0x00007D00, 4byte integer
  header[29] = 0x7D;
  header[30] = 0x00;
  header[31] = 0x00;
  header[32] = 0x02; // BitPerSample*ChannelNum/8 = 2, 2byte integer
  header[33] = 0x00;
  header[34] = 0x10; // BitPerSample:16 = 0x0010, 2byte integer
  header[35] = 0x00;
  header[36] = 'd';
  header[37] = 'a';
  header[38] = 't';
  header[39] = 'a';
  header[40] = (byte)(wavSize & 0xFF);
  header[41] = (byte)((wavSize >> 8) & 0xFF);
  header[42] = (byte)((wavSize >> 16) & 0xFF);
  header[43] = (byte)((wavSize >> 24) & 0xFF);

}


void listSPIFFS(void) {
  Serial.println(F("\r\nListing SPIFFS files:"));
  static const char line[] PROGMEM =  "=================================================";

  Serial.println(FPSTR(line));
  Serial.println(F("  File name                              Size"));
  Serial.println(FPSTR(line));

  fs::File root = SPIFFS.open("/");
  if (!root) {
    Serial.println(F("Failed to open directory"));
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(F("Not a directory"));
    return;
  }

  fs::File file = root.openNextFile();
  while (file) {

    if (file.isDirectory()) {
      Serial.print("DIR : ");
      String fileName = file.name();
      Serial.print(fileName);
    } else {
      String fileName = file.name();
      Serial.print("  " + fileName);
      // File path can be 31 characters maximum in SPIFFS
      int spaces = 33 - fileName.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      String fileSize = (String) file.size();
      spaces = 10 - fileSize.length(); // Tabulate nicely
      if (spaces < 1) spaces = 1;
      while (spaces--) Serial.print(" ");
      Serial.println(fileSize + " bytes");
      
    }

    file = root.openNextFile();
    

    
  }

  Serial.println(FPSTR(line));

  Serial.println();
  delay(1000);
}


#include <HTTPClient.h>
//WiFiClient client;
const char* serverAddress = "http://192.168.43.185:5000/upload"; // 替换为你的Flask服务器地址
void sendFileToServer() {


  // 启动SPIFFS文件系统
  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  
  // 读取.wav文件
  File file = SPIFFS.open("/recording.wav", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  
  // 获取文件大小
  size_t fileSize = file.size();
  Serial.print("File size: ");
  Serial.println(fileSize);
//  Serial.println(file);
//  Serial.println(file.readString().c_str());

  
  // 创建HTTPClient对象
  HTTPClient http;
  
  // 发送HTTP POST请求
  http.begin(serverAddress);
  http.addHeader("Content-Disposition", "attachment; filename=\"file\""); // 替换为与Flask代码中的字段名匹配的名称
  http.addHeader("Content-Type", "audio/wav");
  //int httpCode = http.PUT((uint8_t*)file.readString().c_str(), fileSize);
  int httpCode = http.sendRequest("PUT", &file, fileSize);
  
  // 检查HTTP响应
  Serial.println(file.readString());

  Serial.println(httpCode);
  if (httpCode > 0) {
    String response = http.getString();
    Serial.println("HTTP response: " + response);
  } else {
    Serial.println("HTTP request failed");
  }
  
  // 关闭文件和HTTP连接
  file.close();
  http.end();

 
}
