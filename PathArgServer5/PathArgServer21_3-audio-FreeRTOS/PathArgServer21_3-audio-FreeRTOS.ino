#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include<string.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>
#include "Base64.h"

////////////////////audio
#include <Arduino.h>
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"




//////


#include "FS.h"
#include <LittleFS.h>

/* You only need to format LittleFS the first time you run a
   test or else use the LITTLEFS plugin to create a partition
   https://github.com/lorol/arduino-esp32littlefs-plugin
   
   If you test two partitions, you need to use a custom
   partition.csv file, see in the sketch folder */

//#define TWOPART

#define FORMAT_LITTLEFS_IF_FAILED true



///////






// 任务1
#define TASK1_TASK_PRIO  1          // 任务优先级 server
#define TASK1_STK_SIZE   1024*4       // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle=NULL; // 任务句柄
void task1(void *pvParameters); //任务函数

// 任务2
#define TASK2_TASK_PRIO  1        // 任务优先级 screen
#define TASK2_STK_SIZE   1024*4        // 任务堆栈大小
TaskHandle_t Tasks2_TaskHandle=NULL; // 任务句柄
void task2(void *pvParameters); //任务函数
//
//// 任务3
#define TASK3_TASK_PRIO  1         // 任务优先级 audio
#define TASK3_STK_SIZE   1024*4       // 任务堆栈大小
TaskHandle_t Tasks3_TaskHandle=NULL; // 任务句柄
void task3(void *pvParameters); //任务函数
//
//



///
// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html



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



/////////////////////////////


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


// Include the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.
#include "jpeg1.h"

//#include "plane.h"
//#include "icon1.h"
//#include "icon2.h"
//#include "icon3.h"

#include "icon_1_1.h"
#include "icon_1_2.h"
#include "icon_1_3.h"
#include "icon_1_4.h"

#include "mainPageHtml.h"

//----------------------------------------------------------------------------------------------------

bool click();

//----------------------------------------------------------------------------------------------------
int array [] ={0,0,0,0,0,0};
int click_push_count = 0;
int click_once_count = 0;
int* drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) ;
void renderJPEG(int xpos, int ypos);



////////////////////////////////////////////////////////////////
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
  Serial.println("");
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



/////////////

//void getEncodedImage(){
//  HTTPClient http;
//  http.begin("http://114.55.178.110/getapic2"); // 替换为服务器的URL
//  http.addHeader("Content-Type", "application/json");
//
//  // JSON 数据
//  String jsonPayload = "{\"key1\":\"value1\",\"key2\":\"value2\"}";
//
//  // 发送POST请求
//  int httpResponseCode = http.POST(jsonPayload);
//  String response = "";
//  if (httpResponseCode > 0) {
//    response = http.getString();
//    Serial.println(httpResponseCode);
//    Serial.println(response);
//  } else {
//    Serial.print("Error code: ");
//    Serial.println(httpResponseCode);
//    response = "error";
//  }
//
//  http.end();
//  int decoded_size = base64_decode((char*)decodedImage, (char*)response.c_str(), 10240*3);
//  
//
//}
////////////

//

//

int maxDecodedSize = 1024*29;
uint8_t decodedImage[1024*29] PROGMEM ={0};
//uint8_t *decodedImage ;
//
//// 动态分配内存
//uint8_t* decodedImage = new uint8_t[maxDecodedSize];

void handleImageUpload() {
  if (server.method() == HTTP_POST) {
    Serial.println("post1");
    String encodedImage = (server.arg("image"));
    Serial.println(sizeof(encodedImage));
    int decoded_size = base64_decode((char*)decodedImage, (char*)encodedImage.c_str(), maxDecodedSize);
     
    Serial.println("post2");
    Serial.println(decoded_size);
   
    server.send(200, "text/plain", "Image received");
    }
  }
//
uint8_t frame_0[1024*6 ] PROGMEM ={0};
uint8_t frame_1[1024*6 ] PROGMEM ={0};
uint8_t frame_2[1024*6 ] PROGMEM ={0};
uint8_t frame_3[1024*6 ] PROGMEM ={0};
uint8_t frame_4[1024*6 ] PROGMEM ={0};
uint8_t frame_5[1024*6 ] PROGMEM ={0};
uint8_t frame_6[1024*6 ] PROGMEM ={0};
uint8_t frame_7[1024*6 ] PROGMEM ={0};

//uint8_t *frame_0 ;
//uint8_t *frame_1 ;
//uint8_t *frame_2 ;
//uint8_t *frame_3 ;
//uint8_t *frame_4 ;
//uint8_t *frame_5 ;
//uint8_t *frame_6 ;
//uint8_t *frame_7 ;




const uint8_t *gif[9] PROGMEM {frame_0,frame_1,frame_2,frame_3,frame_4,frame_5,frame_6,frame_7,};

void handleGIFUpload() {
  if (server.method() == HTTP_POST) {

    
    String frame_index = server.arg("frame_index");
    String encodedImage = server.arg("image");
    Serial.println(frame_index);
// 
//
    if (frame_index =="0"){
//      tft.fillScreen(TFT_BLACK);
      Serial.println( 0);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[0] , (char*)encodedImage.c_str(), 1024*6);
      memset(frame_1,0,sizeof(frame_1)); //set zreo
      memset(frame_2,0,sizeof(frame_2));
      memset(frame_3,0,sizeof(frame_3));
      memset(frame_4,0,sizeof(frame_4));
      memset(frame_5,0,sizeof(frame_5));
      memset(frame_6,0,sizeof(frame_6));
      memset(frame_7,0,sizeof(frame_7));
    
    }
    if (frame_index =="1"){
      Serial.println(1);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[1], (char*)encodedImage.c_str(), 1024*6);
    }
    if (frame_index =="2"){
      Serial.println(2);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[2] , (char*)encodedImage.c_str(), 1024*6);
    }
    if (frame_index =="3"){
      Serial.println(3);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[3] , (char*)encodedImage.c_str(), 1024*6);
    }
    
    if (frame_index =="4"){
      Serial.println( 4);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[4] , (char*)encodedImage.c_str(), 1024*6);
    }
    if (frame_index =="5"){
      Serial.println(5);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[5] , (char*)encodedImage.c_str(), 1024*6);
    }
    if (frame_index =="6"){
      Serial.println(6);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[6] , (char*)encodedImage.c_str(), 1024*6);
    }
    if (frame_index =="7"){
      Serial.println(7);
      Serial.println(sizeof(encodedImage));
      int decoded_size = base64_decode((char*)gif[7] , (char*)encodedImage.c_str(), 1024*6);
    }



    
          

        
    server.send(200, "text/plain", "Image received");

    }
  }







//void handleImageUpload2() {
//  if (server.method() == HTTP_POST) {
////  
//  String encodedImage = server.arg(0);
//  Serial.println("-----------------------------------------");
//  //Serial.println(encodedImage);
////  
//// StaticJsonDocument<64> doc;
////  // Json格式写法,创建一个json消息
////  char json_char_[12500];
////  strcpy(json_char_,json.c_str());
////  DeserializationError error = deserializeJson(doc, json_char_);
////  Serial.println(doc["image"].as<String>()); 
////  String encodedImage = doc["image"].as<String>();
//  int decoded_size = base64_decode((char*)decodedImage, (char*)encodedImage.c_str(), 12500);
//  
//
//    server.send(200, "text/plain", "Image received");
//    }
//  }

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


void loopScreen(){

//如果点击click()便会返回true

  if(click()){
      click_push_count = click_push_count+1;
      if (click_push_count==2){ //短按
        click_once_count +=1;
        }
      if (click_push_count==5){//长按
        click_once_count -=2;
        }
       Serial.println(click_push_count); 
    }

    
  else{
      click_push_count = 1;
      if (click_once_count==0){
          TJpgDec.setJpgScale(1);
          if (array[0]==0){
             tft.fillScreen(TFT_WHITE);
          array[0]=1;
          array[1]=0;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;}
          int pic_length = 16;
          screenInfo(urlInfo,30,180,4);
          for (int i=0;i<pic_length;i++ ){
             TJpgDec.drawJpg( 75, 60,a5[i], a5_size[i]);
             info_list[0] = info_list[1];//屏幕字体刷新
             info_list[1] = info;
             if (click()){break;}
             else delay(100);
             }
           
        }

      if (click_once_count==1){
           TJpgDec.setJpgScale(1);
           if (array[1]==0){
             tft.fillScreen(TFT_WHITE);
             array[0]=0;
             array[1]=1;
             array[2]=0;
             array[3]=0;
             array[4]=0;
             array[5]=0;
             TJpgDec.drawJpg( 60, 60, icon_1_1[0], icon_1_1_size[0]); 
               } 
            //Serial.printf("sizeof(decodedImage)0");
            if (decodedImage[0]!=0)
            { 

              uint16_t w = 0, h = 0;
              TJpgDec.getJpgSize(&w, &h, decodedImage, sizeof(decodedImage));

          
              TJpgDec.drawJpg(0,0,decodedImage, sizeof(decodedImage)); 
              //drawArrayJpeg(decodedImage, sizeof(decodedImage), 0, 0);
            }
            else delay(100);
          
        }

        
      if (click_once_count==2){
           TJpgDec.setJpgScale(1);
           if (array[2]==0){
             tft.fillScreen(TFT_WHITE);
             
             array[0]=0;
             array[1]=0;
             array[2]=1;
             array[3]=0;  
             array[4]=0;
             array[5]=0;}


     
        int pic_length = 8;
        for (int i=0;i<pic_length;i++ ){
          TJpgDec.drawJpg( 0, 0, gif[i], sizeof(gif[i]));
          delay(20);
          
          if (click()){break;}else delay(2);
          
          }



//          TJpgDec.drawJpg( 0, 0, frame_0, sizeof(frame_0));
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_1, sizeof(frame_1)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_2, sizeof(frame_2)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_3, sizeof(frame_3)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_4, sizeof(frame_4)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_5, sizeof(frame_5)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_6, sizeof(frame_6)); 
//          delay(10);
//          TJpgDec.drawJpg( 0, 0, frame_7, sizeof(frame_7)); 
//          delay(10);
//   
 
          
      
          // if (click()){break;}else delay(2);
          // }    
            
    

//      else{
//        int pic_length = 60;
//        for (int i=0;i<pic_length;i++ ){
//          TJpgDec.drawJpg( 0, 0, plane[i], plane_size[i]);
//             if (click()){break;}
//             else delay(2);}
//          }
             
              
    }

      if (click_once_count==3){
        TJpgDec.setJpgScale(1);
          if (array[3]==0){
             tft.fillScreen(TFT_WHITE);
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=1;
             array[4]=0; 
             array[5]=0;}
             TJpgDec.drawJpg(60, 60, icon_1_2[0], icon_1_2_size[0]); // Draw a jpeg image stored in memory

          
        } 

      if (click_once_count==4){
        TJpgDec.setJpgScale(1);
           int * size;
           if (array[4]==0){
             tft.fillScreen(TFT_WHITE);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=1;
             array[5]=0;} 
             TJpgDec.drawJpg( 60, 60, icon_1_3[0], icon_1_3_size[0]); // Draw a jpeg image stored in memory

        }

       if (click_once_count==5){
        TJpgDec.setJpgScale(1);
           int * size;
           if (array[5]==0){
             tft.fillScreen(TFT_WHITE);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=0;
             array[5]=1;} 
             TJpgDec.drawJpg( 60, 60 ,icon_1_4[0], icon_1_4_size[0]); // Draw a jpeg image stored in memory

        }


        
      if (click_once_count>5 || click_once_count<0){
          click_once_count = 0;
        }
    }
}

void setup(void) {
  Serial.begin(9600);
  Serial.println(0); 
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);

  
  int pic_length = 16;
  for (int i=0;i<pic_length;i++ ){
      TJpgDec.drawJpg( 75, 60,a5[i], a5_size[i]);
      screenInfo(info,30,180,4);}
  Serial.println(2); 
  initWIFI();
  Serial.println(3); 
  initServer();
  Serial.println(4); 

  

  xTaskCreate(task1, "task1_task",TASK1_STK_SIZE,NULL,TASK1_TASK_PRIO,NULL); 
  xTaskCreate(task2, "task2_task",TASK2_STK_SIZE,NULL,TASK2_TASK_PRIO,NULL);
  xTaskCreate(task3, "task3_task",TASK3_STK_SIZE,NULL,TASK3_TASK_PRIO,NULL);
  vTaskStartScheduler(); //启动调度
  
}
  
void loop(void) {
}


void task1(void *pvParameters)
{
    while(true)
    {
        //Serial.println("task1 runing........");
        server.handleClient();
        
        vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
    }
}

void task2(void *pvParameters)
{
    while(true)
    {
        //Serial.println("task2 runing........");
        loopScreen();
        vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
    }
    
}

int isPlayAudio = 0;
void task3(void *pvParameters)
{
     while(true)
    {
        //Serial.println("task3 runing........");
        
        if (click_once_count==3 && isPlayAudio==0) {
          initURLaudio();
          isPlayAudio = 1;}
                 
        if (click_once_count==3 && isPlayAudio == 1){
          loopURLaudio();}
        

          
        if (click_once_count!=3){
          isPlayAudio=0;
          }

        
        vTaskDelay(10/portTICK_PERIOD_MS); //等待0.1s
    }
    vTaskDelete( Tasks3_TaskHandle );
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



bool click_B(){

   const int touchPin = 15; // 使用 T0 获取数据
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
     //Serial.println("有触控,灯亮");
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

  
