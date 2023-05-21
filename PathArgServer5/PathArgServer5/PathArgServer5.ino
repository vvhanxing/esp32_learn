#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include<string.h>
#include <uri/UriBraces.h>
#include <uri/UriRegex.h>
#include "Base64.h"

const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

//http://192.168.43.216

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

////////////////////////////////////////////////////////////////

// JPEG decoder library
#include <JPEGDecoder.h>

// Return the minimum of two values a and b
#define minimum(a,b)     (((a) < (b)) ? (a) : (b))

// Include the sketch header file that contains the image stored as an array of bytes
// More than one image array could be stored in each header file.
#include "jpeg1.h"
#include "jpeg2.h"
#include "a2.h"
#include "b1.h"
//#include "b4.h"
#include "b2.h"
#include "mark.h"
//#include "jpeg4.h"
#include "mainPageHtml.h"

// Count how many times the image is drawn for test purposes
// uint32_t icount = 0;
//int i=0;
//----------------------------------------------------------------------------------------------------

bool click();
//----------------------------------------------------------------------------------------------------
int array [] ={0,0,0,0,0};
int click_push_count = 0;
int click_once_count = 0;
int* drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) ;
void renderJPEG(int xpos, int ypos);



////////////////////////////////////////////////////////////////
String urlInfo = "";
String info="hello vivi";
String info_list [] = {info,info};
//
String PictInfo="255,216,255,224,0,16,74,70,73,70,0,1,1,0,0,1,0,1,0,0,255,219,0,67,0,8,6,6,7,6,5,8,7,7,7,9,9,8,10,12,20,13,12,11,11,12,25,18,19,15,20,29,26,31,30,29,26,28,28,32,36,46,39,32,34,44,35,28,28,40,55,41,44,48,49,52,52,52,31,39,57,61,56,50,60,46,51,52,50,255,219,0,67,1,8,9,9,12,11,12,24,13,13,24,50,33,28,33,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,50,255,192,0,17,8,0,10,0,10,3,1,34,0,2,17,1,3,17,1,255,196,0,31,0,0,1,5,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,255,196,0,181,16,0,2,1,3,3,2,4,3,5,5,4,4,0,0,1,125,1,2,3,0,4,17,5,18,33,49,65,6,19,81,97,7,34,113,20,50,129,145,161,8,35,66,177,193,21,82,209,240,36,51,98,114,130,9,10,22,23,24,25,26,37,38,39,40,41,42,52,53,54,55,56,57,58,67,68,69,70,71,72,73,74,83,84,85,86,87,88,89,90,99,100,101,102,103,104,105,106,115,116,117,118,119,120,121,122,131,132,133,134,135,136,137,138,146,147,148,149,150,151,152,153,154,162,163,164,165,166,167,168,169,170,178,179,180,181,182,183,184,185,186,194,195,196,197,198,199,200,201,202,210,211,212,213,214,215,216,217,218,225,226,227,228,229,230,231,232,233,234,241,242,243,244,245,246,247,248,249,250,255,196,0,31,1,0,3,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,10,11,255,196,0,181,17,0,2,1,2,4,4,3,4,7,5,4,4,0,1,2,119,0,1,2,3,17,4,5,33,49,6,18,65,81,7,97,113,19,34,50,129,8,20,66,145,161,177,193,9,35,51,82,240,21,98,114,209,10,22,36,52,225,37,241,23,24,25,26,38,39,40,41,42,53,54,55,56,57,58,67,68,69,70,71,72,73,74,83,84,85,86,87,88,89,90,99,100,101,102,103,104,105,106,115,116,117,118,119,120,121,122,130,131,132,133,134,135,136,137,138,146,147,148,149,150,151,152,153,154,162,163,164,165,166,167,168,169,170,178,179,180,181,182,183,184,185,186,194,195,196,197,198,199,200,201,202,210,211,212,213,214,215,216,217,218,226,227,228,229,230,231,232,233,234,242,243,244,245,246,247,248,249,250,255,218,0,12,3,1,0,2,17,3,17,0,63,0,245,139,217,142,154,110,126,211,125,168,72,33,113,112,74,71,159,148,156,108,30,213,210,69,32,154,20,149,65,10,234,24,2,48,112,125,169,244,82,214,237,176,90,71,151,212,255,217,";

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

/////////////////  
  
  }

//
//   uint8_t pic_uint8_t_0[] PROGMEM = { };
//   uint8_t *pic_uint8_t[1] PROGMEM { pic_uint8_t_0,};
//   uint32_t pic_uint8_t_size[1] PROGMEM { 671,};


//
//  void str2pic(String PictInfo)
//  {
//    Serial.println("start0");
//  
//  String numString="" ;
//  Serial.println("start1");
//
//  Serial.println("start2");
//  int numIndex = 0;
//  for (int i=0;i<PictInfo.length();i++){
//    //Serial.println(numIndex);
//    if(PictInfo[i]!=',')
//      numString += PictInfo[i];
//    else{
//
//      pic_uint8_t_0[numIndex] =(uint8_t)numString.toInt();
//      numIndex++;
//
//    Serial.println(numIndex);
//    Serial.println("---------");
//    Serial.println(numString);
//    Serial.println("--2");
//    Serial.println(atoi( numString.c_str()));
//    Serial.println( numString.toInt());
//    Serial.println( (uint8_t)numString.toInt());
//    Serial.println( pic_uint8_t_0[numIndex]);
//    Serial.println("----");
//      
//      numString="";
//
// 
//
////http post对jpg图片编码并传输图片,ardunio esp32连接 wifi 通过webserver接收图片， tft lcd屏幕显示图片，给出pytohn request代码，以及ardunio代码
//
//      
//      }
//    }
/////
  
 
   
    

    
    
 


WebServer server(80);


  
void initServer(){
  
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



//  
//// 处理HTTP请求，读取上传的图片数据
//void handleImageUpload() {
//  if (server.method() == HTTP_POST) {
//    String image_data = server.arg("image");
//    Serial.println(image_data);
//    if (image_data != "") {
////      unsigned int decoded_size = base64_dec_len((char*)image_data.c_str(), image_data.length());
////      byte* decoded_data = (byte*) malloc(decoded_size);
////      Serial.println(decoded_size);
//      int decoded_size = image_data.length();
//      byte* decoded_data = (byte*) malloc(decoded_size);
//      Serial.println(decoded_size);
//
//      
//      base64_decode((char*) decoded_data, (char*) image_data.c_str(), image_data.length()); 
//      String decoded_string = (char*)decoded_data;
//      Serial.println(decoded_string);
//      free(decoded_data);
//      //Serial.println(decoded_string);
//      int image_size = decoded_string.length();
//      byte* image_bytes = (byte*) malloc(image_size);
//      //Serial.println(image_bytes);
//      decoded_string.getBytes(image_bytes, image_size);
//      
//      tft.pushImage(0, 0, 200, 200, image_bytes);
//      free(image_bytes);
//
//      server.send(200, "text/plain", "Image received");
//    }
//  }
//}
//void handleImageUpload() {
//  if (server.method() == HTTP_POST) {
//    String image_data = server.arg("image");
//    if (image_data != "") {
//      unsigned int decoded_size = base64_dec_len((char*)image_data.c_str(), image_data.length());
//      int decoded_size_int = (int) decoded_size;
//      
//      byte* decoded_data = (byte*) malloc(decoded_size_int);
//      base64_decode((char*) decoded_data, (char*) image_data.c_str(), image_data.length());
//      tft.pushImage(0, 0, 240, 240, decoded_data);
//      free(decoded_data);
//      server.send(200, "text/plain", "Image received");
//      return;
//    }
//  }
//  server.send(400, "text/plain", "Bad Request");
//}
//void handleImageUpload() {
//  if (server.method() == HTTP_POST) {
//    String image_data = server.arg("image");
//    if (image_data != "") {
//      unsigned int decoded_size = base64_dec_len((char*)image_data.c_str(), image_data.length());
//      byte* decoded_data = (byte*) malloc(decoded_size);
//      base64_decode((char*) decoded_data, (char*)image_data.c_str(), image_data.length()); 
//      String decoded_string = (char*)decoded_data;
//      free(decoded_data);
//
//      int image_size = decoded_string.length();
//      byte* image_bytes = (byte*) malloc(image_size);
//      decoded_string.getBytes(image_bytes, image_size);
//
//      tft.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, image_bytes);
//      free(image_bytes);
//
//      server.send(200, "text/plain", "Image received");
//    }
//  }
//}


//
//void handleImageUpload() {
//  if (server.method() == HTTP_POST) {
//    String imageData = server.arg("image");
//    Serial.println(imageData);
////    imageData.trim();
//    uint8_t* image_data = (uint8_t*) malloc(imageData.length() + 1);
//    int decoded_size = base64_decode((char*)image_data, (char*)imageData.c_str(), imageData.length());
//    Serial.println(decoded_size);
//   // tft.pushImage(0, 0, TFT_WIDTH, TFT_HEIGHT, image_data);
//    drawArrayJpeg(image_data, sizeof(image_data), 16, 16);
//    free(image_data);
//    Serial.println("图片显示成功");
//
//    server.send(200, "text/plain", "Image received");
//    }
//  }
//



//
void handleImageUpload() {
  if (server.method() == HTTP_POST) {
  String encodedImage = server.arg("image");
  //size_t decodedSize = base64_decoded_length(encodedImage.length());
  uint8_t decodedImage[4096];

  int decoded_size = base64_decode((char*)decodedImage, (char*)encodedImage.c_str(), 4096);
  tft.pushImage(0, 0, 200, 200, mark[0]);
  //drawArrayJpeg(decodedImage, 4096, 0, 0);

    server.send(200, "text/plain", "Image received");
    }
  }
//


void runServer(){
  initServer();
  //server.on(F("/"), []() {
    //server.send(200, "text/plain", "hello from esp32!");
  //});
  server.on("/",HTTP_GET,MainPage);
  server.on("/putinfo",HTTP_POST,putInfo);
  server.on("/putPageIndex",HTTP_POST,putPageIndex);
  server.on("/getinfo",HTTP_GET,getInfo);
  server.on("/upload_image", handleImageUpload);

  //
  server.begin();
  Serial.println("HTTP server started");

  
  }



void setup(void) {
  Serial.begin(9600);

  

  tft.init();
  tft.setRotation(0);



        
  tft.fillScreen(TFT_WHITE);

  int pic_length = sizeof(a5)/sizeof(a5[0]);
  for (int i=0;i<pic_length;i++ ){
      drawArrayJpeg(a5[i], a5_size[i], 120, 120);
      screenInfo(info,0,0,4);}





//
// for (int i=0;i<671;i++){
//    Serial.println(pic_uint8_t_0[i]);
//    
//  }

  
  //info = WiFi.localIP()
  //screenInfo( info);
  runServer();
}

void loop(void) {
  server.handleClient();
  delay(100);//allow the cpu to switch to other tasks







//如果点击click()便会返回true

  if(click()){
    
      click_push_count = click_push_count+1;
      if (click_push_count==2){
        click_once_count +=1;
        }
      if (click_push_count==5){
        click_once_count -=2;
        }
       Serial.println(click_push_count); 
    }

    
  else{

    click_push_count = 1;
     
      

      if (click_once_count==0){
          if (array[0]==0){
             tft.fillScreen(TFT_WHITE);}
          array[0]=1;
          array[1]=0;
          array[2]=0;
          array[3]=0;
          array[4]=0; 
          int pic_length = sizeof(a5)/sizeof(a5[0]);
          for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(a5[i], a5_size[i], 120, 120);

             info_list[0] = info_list[1];//屏幕刷新
             info_list[1] = info;
             screenInfo(info,0,200,4);
             if (click()){break;}
             else delay(100);
             }


          
        }

      if (click_once_count==1){
           
           if (array[1]==0){
             tft.fillScreen(TFT_WHITE);}
             array[0]=0;
             array[1]=1;
             array[2]=0;
             array[3]=0;
             array[4]=0; 
             
            screenInfo(urlInfo,0,200,4);
            drawArrayJpeg(Tiger, sizeof(Tiger), 4, 0); // Draw a jpeg image stored in memory
            delay(100);

  
        }

        
      if (click_once_count==2){
           if (array[2]==0){
             tft.fillScreen(TFT_WHITE);}
             array[0]=0;
             array[1]=0;
             array[2]=1;
             array[3]=0;  
             array[4]=0; 
             
//      str2pic( PictInfo);
      int pic_length = sizeof(mark)/sizeof(mark[0]);
      for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(mark[i], mark_size[i], 0, 0);
             if (click()){break;}
             else delay(50);
             }
        }

      if (click_once_count==3){
          if (array[3]==0){
             tft.fillScreen(TFT_WHITE);}
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=1;
             array[4]=0; 
      int pic_length = sizeof(b1)/sizeof(b1[0]);
      for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(b1[i], b1_size[i], 0, 0);
             if (click()){break;}
             else delay(50);
             }
          
        } 

      if (click_once_count==4){
           int * size;
           if (array[4]==0){
             tft.fillScreen(TFT_BLACK);
             //size = drawArrayJpeg(b2[0], b2_size[0], 0, 120);
             }
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=1;  
             int pic_length = sizeof(b2)/sizeof(b2[0]);
           for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(b2[i], b2_size[i], 0, 50);
             if (click()){break;}
             else delay(50);
             }
        }

               
        
      if (click_once_count>4 || click_once_count<0){

          click_once_count = 0;
          
        }


    }



  
}











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
