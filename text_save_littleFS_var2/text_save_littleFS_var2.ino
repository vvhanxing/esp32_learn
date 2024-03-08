#include "arduino_base64.hpp"
#include "FS.h"
#include <LittleFS.h>

#define FORMAT_LITTLEFS_IF_FAILED true


void setup(){
   
  Serial.begin(9600);
  if (!LittleFS.begin()) {
    Serial.println("LittleFS initialization failed.");
    return;
  }

  // 创建一个名为data.bin的文件用于保存数据
  File file = LittleFS.open("/data.bin", "w");
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }

  // 假设你有一个名为data的uint8_t数组
  uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05};

  // 将数据写入文件
  file.write(data, sizeof(data));
  file.close();

  Serial.println("Data saved to LittleFS.");   




if (!LittleFS.begin()) {
    Serial.println("LittleFS initialization failed.");
    return;
  }

  // 打开保存数据的文件
  file = LittleFS.open("/data.bin", "r");
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // 确定文件大小并创建一个相应大小的缓冲区
  size_t fileSize = file.size();
  uint8_t* buffer = (uint8_t*)malloc(fileSize);

  // 从文件中读取数据到缓冲区
  file.read(buffer, fileSize);
  file.close();

  // 打印读取的数据
  Serial.println("Data read from LittleFS:");
  for (size_t i = 0; i < fileSize; i++) {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  // 释放缓冲区内存
  free(buffer);




    
}

void loop(){}
