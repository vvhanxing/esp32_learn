#include "arduino_base64.hpp"
#include "FS.h"
#include <LittleFS.h>

#define FORMAT_LITTLEFS_IF_FAILED true

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\r\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("- failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("- file written");
    } else {
        Serial.println("- write failed");
    }
    file.close();
}

String readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\r\n", path);
    String result = "";
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return result;
    }

    Serial.println("- read from file:");
    
    while(file.available()){
        //Serial.write(file.read());
        
        result  +=(char)file.read();
    }
    
    file.close();
    return result;

}


void setup(){
    Serial.begin(115200);
    while(!Serial);

    const uint8_t data[] = {0, 1, 2, 3, 4};
    auto dataLength = sizeof(data);
    char result[base64::encodeLength(dataLength)];

    base64::encode(data, dataLength, result);

    Serial.println(result);


    if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
        return;
    }
      
    writeFile(LittleFS, "/hello2.txt", result);
    String r = readFile(LittleFS, "/hello2.txt");
    Serial.println(r);
    uint8_t data_2[base64::decodeLength(result)];

    base64::decode((char*)r.c_str(), data_2);
    for (int i=0;i<=4;i++){
      Serial.print(data_2[i]);
      }
    
    Serial.print("num:");
      // 

    
}

void loop(){}
