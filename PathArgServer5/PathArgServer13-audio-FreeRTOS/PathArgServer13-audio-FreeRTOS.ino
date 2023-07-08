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



// 任务1
#define TASK1_TASK_PRIO  1          // 任务优先级
#define TASK1_STK_SIZE   1024*8        // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
void task1(void *pvParameters); //任务函数

// 任务2
#define TASK2_TASK_PRIO  1        // 任务优先级
#define TASK2_STK_SIZE   1024*8        // 任务堆栈大小
TaskHandle_t Tasks2_TaskHandle; // 任务句柄
void task2(void *pvParameters); //任务函数
//
//// 任务3
#define TASK3_TASK_PRIO  1         // 任务优先级
#define TASK3_STK_SIZE   1024*8        // 任务堆栈大小
TaskHandle_t Tasks3_TaskHandle; // 任务句柄
void task3(void *pvParameters); //任务函数
//
//



///
// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html



// Randomly picked URL
const char *URL="http://114.55.178.110/audio/mp3";

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



/////////////////////////////


const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

//http://192.168.43.216

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

////////////////////////////////////////////////////////////////

// JPEG decoder library
#include <JPEGDecoder.h>


// Include the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.
#include "jpeg1.h"

#include "plane.h"
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
  // 设置起始坐标(20, 10)，4 号字体
  if (info_list [0]!= info_list [1]){
     tft.fillScreen(TFT_WHITE);
    }
  tft.setCursor(posx, posy);
  // 设置文本颜色为白色，黑色文本背景
  tft.setTextFont(font);
  tft.setTextColor( TFT_BLACK,TFT_WHITE);
  // 设置显示的文字，注意这里有个换行符 \n 产生的效果
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
  info = server.arg("info") ;
  Serial.println(info);
  server.sendHeader("Location","/getinfo");
  server.send(302,"text/plain","ok");
  }

void putPageIndex(){
  Serial.println(server.arg(0));
  String json = server.arg(0);
  StaticJsonDocument<32> doc;
  // Json格式写法，创建一个json消息
  char json_char_[32];
  strcpy(json_char_,json.c_str());
  DeserializationError error = deserializeJson(doc, json_char_);
  Serial.println(doc["click_once_count"].as<String>());  

  click_once_count = doc["click_once_count"].as<String>().toInt() ;
  Serial.println("------1");
  Serial.println(click_once_count);
  server.sendHeader("Location","/getinfo");
  server.send(302,"text/plain","ok");
  }

void getInfo(){
  server.send(200,"text/html",(String)"<!DOCTYPE html><body><h1>"+"info: </h1><h1>"+info+"</h1></body></html>");
  Serial.println("------2");
  Serial.println(info);
  }

uint8_t decodedImage[20000]={0};
void handleImageUpload() {
  if (server.method() == HTTP_POST) {
    Serial.println("post1");
    String encodedImage = server.arg("image");
    Serial.println("post2");
    //Serial.println(encodedImage);
    Serial.println("post3");
    int decoded_size = base64_decode((char*)decodedImage, (char*)encodedImage.c_str(), 20000);
    Serial.println("post4");
    //free(decodedImage);
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
////  // Json格式写法，创建一个json消息
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
 // server.on("/upload_image2", handleImageUpload2);
  server.begin();
  Serial.println("HTTP server started");

  }


void initURLaudio(){

  audioLogger = &Serial;
  file = new AudioFileSourceICYStream(URL);
  file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(file, 2048);
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
          if (array[0]==0){
             tft.fillScreen(TFT_WHITE);
          array[0]=1;
          array[1]=0;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;}
          int pic_length = sizeof(a5)/sizeof(a5[0]);
          screenInfo(urlInfo,30,180,4);
          for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(a5[i], a5_size[i], 75, 60);
             info_list[0] = info_list[1];//屏幕字体刷新
             info_list[1] = info;
             if (click()){break;}
             else delay(100);
             }
           
        }

      if (click_once_count==1){
           if (array[1]==0){
             tft.fillScreen(TFT_WHITE);
             array[0]=0;
             array[1]=1;
             array[2]=0;
             array[3]=0;
             array[4]=0;
             array[5]=0;}        
            if (decodedImage[0]!=0)
            drawArrayJpeg(decodedImage, sizeof(decodedImage), 0, 0);//http图片
            else  drawArrayJpeg(icon_1_1[0], icon_1_1_size[0], 60, 60); // Draw a jpeg image stored in memory
            delay(100);
        }

        
      if (click_once_count==2){
           if (array[2]==0){
             tft.fillScreen(TFT_WHITE);
             
             array[0]=0;
             array[1]=0;
             array[2]=1;
             array[3]=0;  
             array[4]=0;
             array[5]=0;}

      int pic_length = sizeof(plane)/sizeof(plane[0]);
      for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(plane[i], plane_size[i], 0, 0);
             if (click()){break;}
             else delay(2);
             
             }
             
              
        }

      if (click_once_count==3){
          if (array[3]==0){
             tft.fillScreen(TFT_WHITE);
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=1;
             array[4]=0; 
             array[5]=0;}
             drawArrayJpeg(icon_1_2[0], icon_1_2_size[0], 60, 60); // Draw a jpeg image stored in memory

          
        } 

      if (click_once_count==4){
           int * size;
           if (array[4]==0){
             tft.fillScreen(TFT_WHITE);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=1;
             array[5]=0;} 
             drawArrayJpeg(icon_1_3[0], icon_1_3_size[0], 60, 60); // Draw a jpeg image stored in memory

        }

if (click_once_count==5){
           int * size;
           if (array[5]==0){
             tft.fillScreen(TFT_WHITE);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=0;
             array[5]=1;} 
             drawArrayJpeg(icon_1_4[0], icon_1_4_size[0], 60, 60); // Draw a jpeg image stored in memory

        }


        
      if (click_once_count>5 || click_once_count<0){
          click_once_count = 0;
        }
    }
}

void setup(void) {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);
  int pic_length = sizeof(a5)/sizeof(a5[0]);
  for (int i=0;i<pic_length;i++ ){
      drawArrayJpeg(a5[i], a5_size[i], 75, 60);
      screenInfo(info,30,180,4);}

  initWIFI();
  initServer();
 

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
}








// Return the minimum of two values a and b
#define minimum(a,b)     (((a) < (b)) ? (a) : (b))
//####################################################################################################
// Draw a JPEG on the TFT pulled from a program memory array
//####################################################################################################
int* drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) {

  int x = xpos;
  int y = ypos;

  JpegDec.decodeArray(arrayname, array_size);
  
  //jpegInfo(); // Print information from the JPEG file (could comment this line out)
  
  renderJPEG(x, y);
  int size [] ={0,0};
  size[0] = JpegDec.width;
  size[1] = JpegDec.height;
  return size;
  //Serial.println("#########################");
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void renderJPEG(int xpos, int ypos) {

  // retrieve infomration about the image
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
  uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  //uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // read each MCU block until there are no more
  while (JpegDec.readSwappedBytes()) {
    
    // save a pointer to the image block
    pImg = JpegDec.pImage ;

    // calculate where the image block should be drawn on the screen
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;  // Calculate coordinates of top left corner of current MCU
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w)
    {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++)
      {
        p += mcu_w;
        for (int w = 0; w < win_w; w++)
        {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // draw image MCU block only if it will fit on the screen
    if (( mcu_x + win_w ) <= tft.width() && ( mcu_y + win_h ) <= tft.height())
    {
      tft.pushRect(mcu_x, mcu_y, win_w, win_h, pImg);
    }
    else if ( (mcu_y + win_h) >= tft.height()) JpegDec.abort(); // Image has run off bottom of screen so abort decoding
  }

  // calculate how long it took to draw the image
  //drawTime = millis() - drawTime;

  // print the results to the serial port
  //Serial.print(F(  "Total render time was    : ")); Serial.print(drawTime); Serial.println(F(" ms"));
  //Serial.println(F(""));
}

//####################################################################################################
// Print image information to the serial port (optional)
//####################################################################################################
void jpegInfo() {
  Serial.println(F("==============="));
  Serial.println(F("JPEG image info"));
  Serial.println(F("==============="));
  Serial.print(F(  "Width      :")); Serial.println(JpegDec.width);
  Serial.print(F(  "Height     :")); Serial.println(JpegDec.height);
  Serial.print(F(  "Components :")); Serial.println(JpegDec.comps);
  Serial.print(F(  "MCU / row  :")); Serial.println(JpegDec.MCUSPerRow);
  Serial.print(F(  "MCU / col  :")); Serial.println(JpegDec.MCUSPerCol);
  Serial.print(F(  "Scan type  :")); Serial.println(JpegDec.scanType);
  Serial.print(F(  "MCU width  :")); Serial.println(JpegDec.MCUWidth);
  Serial.print(F(  "MCU height :")); Serial.println(JpegDec.MCUHeight);
  Serial.println(F("==============="));
}

//####################################################################################################
// Show the execution time (optional)
//####################################################################################################
// WARNING: for UNO/AVR legacy reasons printing text to the screen with the Mega might not work for
// sketch sizes greater than ~70KBytes because 16 bit address pointers are used in some libraries.

// The Due will work fine with the HX8357_Due library.

void showTime(uint32_t msTime) {
  //tft.setCursor(0, 0);
  //tft.setTextFont(1);
  //tft.setTextSize(2);
  //tft.setTextColor(TFT_WHITE, TFT_BLACK);
  //tft.print(F(" JPEG drawn in "));
  //tft.print(msTime);
  //tft.println(F(" ms "));
  Serial.print(F(" JPEG drawn in "));
  Serial.print(msTime);
  Serial.println(F(" ms "));
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
