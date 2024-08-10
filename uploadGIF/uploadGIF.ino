#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include<string.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>
#include "Base64.h"

#include "arduino_base64.hpp"
//#include "Free_Fonts.h" 

#include "FS.h"
#include <LittleFS.h>

/* You only need to format LittleFS the first time you run a
   test or else use the LITTLEFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin
   
   If you test two partitions, you need to use a custom
   partition.csv file, see in the sketch folder */

//#define TWOPART

#define FORMAT_LITTLEFS_IF_FAILED true



const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

//http://192.168.43.216

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

////////////////////////////////////////////////////////////////

// JPEG decoder library
// Include the jpeg decoder library
#include <TJpg_Decoder.h>
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}


#include "mainPageHtml.h"

int* drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) ;
void renderJPEG(int xpos, int ypos);

String urlInfo = "";
String info="hello vivi";
String info_list [] = {info,info};




///////////////////
void screenInfo(String info,int posx, int posy ,int font){
  // 设置起始坐标(20, 10),4 号字体
  if (info_list [0]!= info_list [1]){
     tft.fillScreen(TFT_WHITE);
    }
  tft.setCursor(posx, posy);
  // 设置文本颜色为白色,黑色文本背景
  tft.setTextFont(font);
  tft.setTextColor( TFT_BLACK,TFT_WHITE);
  // 设置显示的文字,注意这里有个换行符 \n 产生的效果
  tft.println(info);
  }

/////////////////  
WebServer server(80);
void initWIFI(){
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("123");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  urlInfo = WiFi.localIP().toString();
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
      }
  }

void MainPage(){
  server.send(200,"text/html",mainPageHtmlString(urlInfo));
  Serial.println("MainPage");
  }
  
void putInfo(){
//  info = server.arg("info") ;
//  Serial.println(info);
//
//
//  Serial.println(server.arg(0));
  String json = server.arg(0);
  StaticJsonDocument<32> doc;
  // Json格式写法,创建一个json消息
  char json_char_[32];
  strcpy(json_char_,json.c_str());
  DeserializationError error = deserializeJson(doc, json_char_);
  Serial.println(doc["info"].as<String>()); 
  info =  doc["info"].as<String>();

  server.sendHeader("Location","/getinfo");
  server.send(200,"text/plain","ok");
  //
//         
//case 4: // Mirror and rotate counterclockwise
//#ifdef CGRAM_OFFSET
//  if (_init_width == 240 && _init_height == 240)  // Assuming square screen
//  {
//    colstart = 0;  // Adjust this value based on your mirroring requirements
//    rowstart = 0;    // Adjust this value based on your mirroring requirements
//  }
//  else
//  {
//    // Adjust these values based on your mirroring requirements for non-square screens
//    colstart = 0;
//    rowstart = 0;
//  }
//#endif
//  writedata(TFT_MAD_MX  | TFT_MAD_COLOR_ORDER);  // Adjust rotation direction if needed
// 
//  _width  = _init_height;
//  _height = _init_width;  E:\Arduino\hardware\espressif\esp32\libraries\TFT_eSPI\TFT_Drivers\ST7735_Rotation.h
//  break;
  if (info=="rotate0") {tft.setRotation(0);tft.fillScreen(TFT_WHITE);}
  if (info=="rotate90") {tft.setRotation(1);tft.fillScreen(TFT_WHITE);}
  if (info=="rotate180") {tft.setRotation(2);tft.fillScreen(TFT_WHITE);}
  if (info=="rotate270") {tft.setRotation(3);tft.fillScreen(TFT_WHITE);}
  if (info=="mirror") {tft.setRotation(4);tft.fillScreen(TFT_WHITE);}
  }
int click_once_count = 0;

  
void getInfo(){
  server.send(200,"text/html",(String)"<!DOCTYPE html><body><h1>"+"info: </h1><h1>"+info+"</h1></body></html>");
  Serial.println("------2");
  //getEncodedImage();
  Serial.println(info);
  
  }

  
void putPageIndex(){
  Serial.println(server.arg(0));
  String json = server.arg(0);
  StaticJsonDocument<32> doc;
  // Json格式写法,创建一个json消息
  char json_char_[32];
  strcpy(json_char_,json.c_str());
  DeserializationError error = deserializeJson(doc, json_char_);
  Serial.println(doc["info"].as<String>());  

  click_once_count = doc["info"].as<String>().toInt() ;
  Serial.println("------1");
  Serial.println(info);
  server.sendHeader("Location","/getinfo");
  server.send(302,"text/plain","ok");
  }




//

//

int maxDecodedSize = 1024*32;
uint8_t decodedImage[1024*32 ] PROGMEM ={0};

void handleImageUpload() {
  if (server.method() == HTTP_POST) {
    Serial.println("post1");
    
    String encodedImage = server.arg("image");
    Serial.println(sizeof(encodedImage));
    int decoded_size = base64_decode((char*)decodedImage, (char*)encodedImage.c_str(), maxDecodedSize);
     
    Serial.println("post2");
    Serial.println(decoded_size);
   
    server.send(200, "text/plain", "Image received");
    }
  }


#define FORMAT_LITTLEFS_IF_FAILED true

uint8_t frame_0[1024*16 ] PROGMEM ={0};
uint8_t frame_1[1024*16 ] PROGMEM ={0};

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

String*  listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\r\n", dirname);
    String dir_list [24] ;
    File root = fs.open(dirname);
    if(!root){
        Serial.println("- failed to open directory");
        return dir_list;
    }
    if(!root.isDirectory()){
        Serial.println(" - not a directory");
        return dir_list;
    }

    File file = root.openNextFile();
    int i = 0;
    while(file){
      
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            dir_list[i] = file.name();
            i++;
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            dir_list[i] = file.name();
            i++;            
            Serial.print("\tSIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
        return dir_list;
        
    }
}


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
    //Serial.printf("Reading file: %s\r\n", path);
    String result = "";
    File file = fs.open(path);
    if(!file || file.isDirectory()){
        Serial.println("- failed to open file for reading");
        return result;
    }

    //Serial.println("- read from file:");
    
    while(file.available()){
        //Serial.write(file.read());
        
        result  +=(char)file.read();
    }
    
    file.close();
    return result;

}



int frame_num = 0;
uint8_t frame_info[] = {0,240,0}; //num,w,h
int image_hight=0;
void handleGIFUpload() {
  if (server.method() == HTTP_POST) {

    
    String frame_index = server.arg("frame_index");
    String encodedImage = server.arg("image");
    image_hight =server.arg("image_height").toInt();
    
    Serial.println(frame_index);
    Serial.println("image_hight");
    Serial.println(image_hight);
    
    
// 
   
    
      Serial.println( 0);
      Serial.println(sizeof(encodedImage));
      if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
        Serial.println("LittleFS Mount Failed");
        return;
    }
      createDir(LittleFS, "/gif");
//      writeFile(LittleFS, (char*)("/gif/gif"+frame_index+".txt").c_str(), (char*)encodedImage.c_str());  //(char*)r.c_str()

        File file_w = LittleFS.open((char*)("/gif/gif"+frame_index+".bin").c_str(), "w");
        if (!file_w) {
          Serial.println("Failed to open file for writing");
        }
          // 将数据写入文件
        base64::decode((char*) encodedImage.c_str(), frame_0);
        file_w.write(frame_0, sizeof(frame_0));
        file_w.close();
        Serial.println("Data saved to LittleFS.");  


        Serial.println("Data saved to LittleFS."); 

      
      frame_num = frame_index.toInt();
      if (frame_num==0)tft.fillScreen(TFT_BLACK);
      
      Serial.println("frame_num");
      Serial.println(frame_num);
        frame_info[0] = frame_num;
        frame_info[2] = image_hight;
        
        
 
    
 
   

        
    server.send(200, "text/plain", "Image received");

    }
  }








void initServer(){
 
  server.on("/",HTTP_GET,MainPage);
  server.on("/putinfo",HTTP_POST,putInfo);
  server.on("/putPageIndex",HTTP_POST,putPageIndex);
  server.on("/getinfo",HTTP_GET,getInfo);
  server.on("/upload_image", handleImageUpload);
  server.on("/upload_gif", handleGIFUpload);
  server.begin();
  Serial.println("HTTP server started");

  }

//
//
//String r ="";
//
//
//



void setup(void) {
  Serial.begin(9600);
  Serial.println(0); 
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);

  
  int pic_length = 16;

  Serial.println(2); 
  initWIFI();
  Serial.println(3); 
  initServer();
  Serial.println(4); 

}

void loop() {
  // put your main code here, to run repeatedly:
          server.handleClient();
          for (int i=0; i<frame_info[0];i++){
          //Serial.println((char*)("/gif/gif"+String(i)+".txt").c_str()); 
          //r = readFile(LittleFS, (char*)("/gif/gif"+String(i)+".txt").c_str());
          //base64::decode((char*) r.c_str(), frame_0);
            File file_ = LittleFS.open((char*)("/gif/gif"+String(i)+".bin").c_str(), "r");
            if (!file_) {
            Serial.println("Failed to open file for reading");
            }
            size_t fileSize = file_.size();
             // 从文件中读取数据到缓冲区
             file_.read(frame_1, fileSize);
             TJpgDec.drawJpg( 0, (int)((240-frame_info[2])/2), frame_1, sizeof(frame_1));
             file_.close();
             //free(buffer);

          //


          
          //tft.drawString(String(i)+" "+"Picture", 80, 180, GFXFF);
        
           delay(10);}
           delay(4);

          
}
