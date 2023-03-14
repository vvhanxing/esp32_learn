#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

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
#include "b4.h"
#include "mark.h"
//#include "jpeg4.h"

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

String info="hello vivi";
String info_list [] = {info,info};
//

///////////////////
void screenInfo(String info){
  // 设置起始坐标(20, 10)，4 号字体
  if (info_list [0]!= info_list [1]){
     tft.fillScreen(TFT_WHITE);
    }
 
  tft.setCursor(0, 0);
  // 设置文本颜色为白色，黑色文本背景
  tft.setTextFont(4);
  tft.setTextColor( TFT_BLACK,TFT_WHITE);
  // 设置显示的文字，注意这里有个换行符 \n 产生的效果
  tft.println(info);

/////////////////  
  
  }


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

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
      }

  }


void getInfo(){
  info = server.arg("info") ;
  //screenInfo(info);
  Serial.println("------1");
  Serial.println(info);
  server.sendHeader("Location","/putinfo");
  server.send(302,"text/plain","ok");
  }

void putInfo(){
  server.send(200,"text/html",(String)"<!DOCTYPE html><body><h1>"+"info: </h1><h1>"+info+"</h1></body></html>");
  Serial.println("------2");
  Serial.println(info);
  }

void runServer(){
  initServer();
  //server.on(F("/"), []() {
    //server.send(200, "text/plain", "hello from esp32!");
  //});

  server.on("/putinfo",HTTP_GET,putInfo);
  server.on("/getinfo",HTTP_POST,getInfo);
  
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
      screenInfo(info);}








  
  //info = WiFi.localIP()
  screenInfo( info);
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
             screenInfo(info);
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
      int pic_length = sizeof(a2)/sizeof(a2[0]);
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
             //size = drawArrayJpeg(b4[0], b4_size[0], 0, 120);
             }
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=1;  
             int pic_length = sizeof(b4)/sizeof(b4[0]);
           for (int i=0;i<pic_length;i++ ){
             drawArrayJpeg(b4[i], b4_size[i], 0, 50);
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
