/*
 * Pong
 * Original Code from https://github.com/rparrett/pongclock
 *
 */

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB
#define YELLOW  0x7FCC0//0x78EC//0x229EC//0x668AF//0x661E5  //

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
// JPEG decoder library
#include <JPEGDecoder.h>
int* drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) ;
void renderJPEG(int xpos, int ypos);
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

int16_t h = 240;
int16_t w = 240;


int16_t dashline_h = 4;
int16_t dashline_w = 2;
int16_t dashline_n = h / dashline_h;
int16_t dashline_x = 2*w / 3 - 20;
int16_t dashline_y = dashline_h / 2;



#include "icon1a.h"
#include "icon2a.h"
#include "icon3a.h"
#include "icon4a.h"
#include "icon5a.h"
#include "icon6a.h"
#include "b3.h"
#include "a9.h"
#include "xihaicheng.h"
#include "Free_Fonts.h" 



int clickA_push_count = 0;
int clickA_once_count = 0;

int clickB_push_count = 0;
int clickB_once_count = 0;

int clickC_push_count = 0;
int clickC_once_count = 0;


int array [] ={0,0,0,0,0,0};
int array_0 [] ={0,0,0,0,0,0};
void renderPage(int index);
int p1 = 0;
void setup(void) {
  Serial.begin(9600);
  randomSeed(analogRead(0)*analogRead(1));
   
  tft.init();

  tft.setRotation(0);

  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_BLACK, TFT_WHITE);

  renderPage(0);

  //delay(1000);
  
}

void loop() {

  runOS();


}




void runOS(){
  

//
//            if (clickB()) {
//              clickB_once_count =1;
//              clickC_once_count =0;
//              //p1++;
//              //tft.fillRect(0, 0 , 120 , 240, TFT_WHITE);
//              //tft.fillRect(0, 10+p1 , 50 , 100+p1, YELLOW);
//              delay(10);
//              //Serial.println(clickB()); 
//              }
////      
////
//            if (clickC()) {
//               clickB_once_count =0;
//              clickC_once_count =1;
//              //p1--;
//              //tft.fillRect(0, 0 , 120 , 240, TFT_WHITE);
//              //tft.fillRect(0, 10 +p1, 50 , 100+p1, YELLOW);
//              //Serial.println(clickC()); 
//              delay(10);
//              }








  
  if(clickA()){
      clickA_push_count = clickA_push_count+1;
      if (clickA_push_count==2){ //短按
        clickA_once_count +=1;
        
        }
      if (clickA_push_count==100){//长按
        clickA_once_count -=2;
        
        }
       
       Serial.println(clickA_push_count); 
    }

    else{
      clickA_push_count = 1;


      if (clickA_once_count==0){
          if (array[0]==0){
            
          renderPage(0);
          array[0]=1;
          array[1]=0;
          array[2]=0;
          array[3]=0;
          array[4]=0;
          array[5]=0;
          
          }

          if(clickB()){
              clickB_push_count = clickB_push_count+1;
              if (clickB_push_count==2){
                
                  clickB_once_count +=1;
                  }
                  }

          else{
            clickB_push_count = 1;
            if (clickB_once_count==1){
                 
                 if (array_0[0]==0){
                  array_0[0]=1;
                  array_0[1]=0;
                  array_0[2]=0;
                  tft.fillScreen(TFT_BLACK);
                  
                  }

              
              int pic_length = sizeof(b3)/sizeof(b3[0]);
              for (int i=0;i<pic_length;i++ ){
                  drawArrayJpeg(b3[i], b3_size[i], 10, 10);

                  if (clickC()){
                  clickB_once_count = 0;
                  array_0[0]=0;
                  renderPage(0);
                  
                  
                      break;}
                  

                  if(clickB()){
                    clickB_push_count = clickB_push_count+1;
                    if (clickB_push_count==2){
                        clickB_once_count +=1;
                      break;}}

                      
                      
               else delay(100);              
              
              }
            
            }



            if (clickB_once_count==2){
              
                 
                 if (array_0[1]==0){
                  array_0[0]=0;
                  array_0[1]=1;
                  array_0[2]=0;
                  tft.fillScreen(TFT_BLACK);
                  
                  }

                  
            
              
              int pic_length = sizeof(xihaicheng)/sizeof(xihaicheng[0]);
              for (int i=0;i<pic_length;i++ ){
                  drawArrayJpeg(xihaicheng[i], xihaicheng_size[i], 10, 50);

                  if (clickC()){
                  clickB_once_count = 0;
                  renderPage(0);
                  
                      break;}

                  if(clickB()){
                  clickB_push_count = clickB_push_count+1;
                  if (clickB_push_count==2){
                      clickB_once_count +=1;
                      break;}}


                      
               else delay(100);              
              
              }
            
            }



            if (clickB_once_count==3){
              
                 
                 if (array_0[2]==0){
                  array_0[0]=0;
                  array_0[1]=0;
                  array_0[2]=1;
                  tft.fillScreen(TFT_BLACK);
                  
                  }

                  
             
              
              int pic_length = sizeof(a9)/sizeof(a9[0]);
              for (int i=0;i<pic_length;i++ ){
                  drawArrayJpeg(a9[i], a9_size[i], 10, 50);

                  if (clickC()){
                  clickB_once_count = 0;
                  renderPage(0);
                  
                      break;}

                  if(clickB()){
                  clickB_push_count = clickB_push_count+1;
                  if (clickB_push_count==2){
                      clickB_once_count +=1;
                      break;}}


                      
               else delay(100);              
              
              }
            
            }



            if (clickB_once_count>3) clickB_once_count=1;



            
          }


//          if (clickB()){
//              clickB_once_count = 1;
//           
//              clickB_push_count+=1;
//
//              if (clickB_push_count==2)
//                  
//            {}
//            
//                   }
//                   
//          if (clickB_push_count==1 ){
//          
//              int pic_length = sizeof(b3)/sizeof(b3[0]);
//              for (int i=0;i<pic_length;i++ ){
//                  drawArrayJpeg(b3[i], b3_size[i], 10, 10);
//
//                  if (clickC()){
//                  clickB_once_count = 0;
//                  renderPage(0);
//                  for (int t=0;t<20;t++){
//                      drawArrayJpeg(icon1a[0], icon1a_size[0], t-10, 120-50); }
//                      break;}
//               else delay(100);
//             }
//
//          }
             


          if (clickA_push_count==2){
          
              int pic_length = sizeof(xihaicheng)/sizeof(xihaicheng[0]);
              for (int i=0;i<pic_length;i++ ){
                  drawArrayJpeg(xihaicheng[i], xihaicheng_size[i], 10, 10);

                  if (clickC()){
                  clickB_once_count = 0;
                  renderPage(0);
                  for (int t=0;t<20;t++){
                      drawArrayJpeg(icon1a[0], icon1a_size[0], t-10, 120-50); }
                      break;}
               else delay(100);
             }

          }






 
           
        }

      if (clickA_once_count==1){
           if (array[1]==0){
             renderPage(1);
             array[0]=0;
             array[1]=1;
             array[2]=0;
             array[3]=0;
             array[4]=0;
             array[5]=0;
         
               } 
                 
//            if (decodedImage[0]!=0)
//            drawArrayJpeg(decodedImage, sizeof(decodedImage), 0, 0);//http图片
//            else  drawArrayJpeg(icon_1_1[0], icon_1_1_size[0], 60, 60); // Draw a jpeg image stored in memory
//            delay(100);
        }

        
      if (clickA_once_count==2){
           if (array[2]==0){
             renderPage(2);
             
             array[0]=0;
             array[1]=0;
             array[2]=1;
             array[3]=0;  
             array[4]=0;
             array[5]=0;

          
             
             }

//      int pic_length = sizeof(plane)/sizeof(plane[0]);
//      for (int i=0;i<pic_length;i++ ){
//             drawArrayJpeg(plane[i], plane_size[i], 0, 0);
//             if (clickA()){break;}
//             else delay(2);
//             
//             }
             
              
        }

      if (clickA_once_count==3){
          if (array[3]==0){
             renderPage(3);
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=1;
             array[4]=0; 
             array[5]=0;

          
             
             
             }
             //drawArrayJpeg(icon_1_2[0], icon_1_2_size[0], 60, 60); // Draw a jpeg image stored in memory

          
        } 

      if (clickA_once_count==4){
           int * size;
           if (array[4]==0){
             renderPage(4);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=1;
             array[5]=0;


         
             
             } 
            // drawArrayJpeg(icon_1_3[0], icon_1_3_size[0], 60, 60); // Draw a jpeg image stored in memory

        }

      if (clickA_once_count==5){
           int * size;
           if (array[5]==0){
             renderPage(5);

             
             array[0]=0;
             array[1]=0;
             array[2]=0;
             array[3]=0;  
             array[4]=0;
             array[5]=1;


             
             
             } 
             

        }


        


      
      
      if (clickA_once_count>5 || clickA_once_count<0){
          clickA_once_count = 0;
        }





        
  }  
  
  
  }
 
      


void renderPage(int index){
 //tft.fillScreen(TFT_WHITE);
 tft.fillRect(0, 0 , 120 , 240, TFT_WHITE);
 tft.fillRect(120, 0 , 120 , 240, YELLOW);

//tft.fillRect(225, 40 , 2 , 190, TFT_WHITE);//bar
//tft.fillRect(225-8, 40 , 8 , 20, TFT_WHITE);//bar
              //x  y  dx  dy 

 
 String page[] = {"Video.","Music.","Game.","Image.","MSG.","Setting."};


        tft.setFreeFont(FF23);                 // Select the font
        tft.setTextColor(TFT_WHITE, YELLOW);
        tft.drawString("MENU",-40+ 2*w/3 +10, 4, GFXFF);

  
  bool txt_ani = true;
  for (int i = 0;i<6;i++){
    if (i!=index)
      {
          tft.setFreeFont(FF21);                 // Select the font
           tft.setTextColor(TFT_WHITE, YELLOW);
        tft.drawString(page[i],   2*w/3-5, 35*i +40, GFXFF);
      
      }
    else
      {
        tft.setFreeFont(FF22);                 // Select the font
        tft.setTextColor(TFT_WHITE, YELLOW);
        
        if (txt_ani==true){
        for (int j =0;j<30;j++){

        tft.drawString(page[i],-j+ 2*w/3-5, 35*i +40, GFXFF);}
        
      
        txt_ani = false;
        }
        
      }
      

      
    //tft.fillRect(0, 40*index-20,    20,  40*index+20, TFT_BLACK); //20-60   60-100  100-140
    
      
    
    }




          if(index==0){
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon1a[0], icon1a_size[0], t-10, 120-50); }
          if(index==1){
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon2a[0], icon2a_size[0], t-10, 120-50); }
          if(index==2){
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon3a[0], icon3a_size[0], t-10, 120-50); }
          if(index==3){   
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon4a[0], icon4a_size[0], t-10, 120-50); }
          if(index==4){   
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon5a[0], icon5a_size[0], t-10, 120-50); }
          if(index==5){   
          for (int t=0;t<20;t++)
          drawArrayJpeg(icon6a[0], icon6a_size[0], t-10, 120-50); }


//
//  tft.startWrite();
//
//  // Quick way to draw a dashed line
//  tft.setAddrWindow(dashline_x, 0, dashline_w, h);
//  
//  for(int16_t i = 0; i < dashline_n; i+=2) {
//    tft.pushColor(WHITE, dashline_w*dashline_h); // push dash pixels
//    tft.pushColor(BLACK, dashline_w*dashline_h); // push gap pixels
//  }
//
//  tft.endWrite();

  
  }


bool clickA(){

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


bool clickB(){

   const int touchPin = T4; // 使用 T0 获取数据
   const int threshold = 40;
   
   int touchValue;
  
  touchValue = touchRead(touchPin);
  
  if(touchValue < threshold){
   
     //Serial.println("有触控，灯亮");
    return true;
  }
  else{
    
    return false;
  }
  //delay(500);  
  }

bool clickC(){

   const int touchPin = T5; // 使用 T0 获取数据
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
