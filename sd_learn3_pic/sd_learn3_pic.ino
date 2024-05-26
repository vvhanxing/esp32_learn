#include <Arduino.h>
/*
  SD Card Interface code for ESP32
  SPI Pins of ESP32 SD card as follows:
  CS    = 23;
  MOSI  = 17;
  MISO  = 2;
  SCK   = 16;
*/

#include <SPI.h>
#include <SD.h>
///

#define BLACK 0x0000
#define WHITE 0xFFFF
#define GREY  0x5AEB
#define YELLOW  0x7FCC0//0x78EC//0x229EC//0x668AF//0x661E5  //
#include "Free_Fonts.h" 
int16_t h = 240;
int16_t w = 240;
String page[12] ;

// os



int clickA_push_count = 0;
//int clickA_once_count = 0;

int clickB_push_count = 0;
//int clickB_once_count = 0;

int clickC_push_count = 0;
//int clickC_once_count = 0;






// 定义一个文件对象
File myFile; 

const int CS = 22; // 定义SPI通信中CS（Chip Select）信号的常量
const int MOSI_PIN = 4; // 定义SPI通信中MOSI（Master Out Slave In）信号的常量
const int SCK_PIN = 16; // 定义SPI通信中SCK（Serial Clock）信号的常量
const int MISO_PIN = 18; // 定义SPI通信中MISO（Master In Slave Out）信号的常量


// 定义一个自定义的SPI类实例
SPIClass CustomSPI;
/**
 * @brief 将指定消息写入到文件中。
 * 
 * @param path 指向要写入的文件路径的字符指针。
 * @param message 指向要写入文件的消息的字符指针。
 * 说明：函数不返回任何值，但会在串口打印操作的结果。
 */
void WriteFile(const char *path, const char *message)
{
  // 尝试打开文件以便写入
  myFile = SD.open(path, FILE_WRITE);
  if (myFile)
  {
    // 打印正在写入的文件路径
    Serial.printf("Writing to %s ", path);
    // 写入消息到文件，并在末尾添加换行符
    myFile.println(message);
    // 关闭文件
    myFile.close(); 
    // 打印写入操作完成的通知
    Serial.println("completed.");
  }

  else
  {
    // 打印打开文件失败的通知
    Serial.println("error opening file ");
    // 打印失败的文件路径
    Serial.println(path);
  }
}

String fileList [512] = {""};
int fileIndex = 0;
String dirList [512] = {""};
int dirIndex = 0;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);
    
    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return ;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return ;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            dirList[dirIndex] = file.name();
            dirIndex+=1;
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
            fileList[fileIndex] = file.name();
            fileIndex+=1;
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

/**
 * 读取指定路径的文件
 * 
 * @param path 指向要打开的文件路径的字符指针
 * 
 * 该函数尝试打开指定路径的文件，如果成功打开，则逐字节读取文件内容并通过串口打印。
 * 如果无法打开文件，将打印错误信息。
 */
String ReadFile_txt(const char *path)
{
  myFile = SD.open(path); // 尝试打开文件
  String result = "";
  if (myFile) // 如果文件成功打开
  {
    Serial.printf("Reading file from %s\n", path); // 打印读取文件的路径信息
    while (myFile.available()) // 循环读取文件中的所有内容
    {
      //Serial.write(myFile.read()); // 将读取到的每个字节通过串口发送
      result  += (char)myFile.read();
    }
    myFile.close(); // 关闭文件
    return result;
  }
  else // 如果文件打开失败
  {
    Serial.println("error opening test.txt"); // 打印错误信息
    return result;
  }
}

/**
 * @brief 初始化设置函数
 * 该函数主要完成以下初始化工作：
 * 1. 初始化串口通信，设置波特率为9600；
 * 2. 初始化自定义SPI通信，并传入SCK、MISO、MOSI引脚及CS控制信号；
 * 3. 等待串口完全初始化；
 * 4. 初始化SD卡，如果初始化失败则打印错误信息并返回；
 * 5. 写入测试文件"/test.txt"；
 * 6. 读取测试文件"/test.txt"的内容。
 * 
 * 该函数没有参数和返回值。
 */

////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

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




#include "arduino_base64.hpp"




uint8_t frame_0[1024*32 ] PROGMEM ={0};



////////////////////////////////////////////////////

int OSIndexMap[16][3] = {
  {1,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0},
  {0,0,0}
  };
int OSIndexX = 0;
int OSIndexY = 0;
int (*pRanderPage)(int);

////////////////////////////////
void setup()
{
  // 初始化串口通信，设置波特率为9600，并延迟500ms
  Serial.begin(9600);
  delay(500);


///////////////////////////////////
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_WHITE);

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);

  tft.setTextColor(TFT_BLACK, TFT_WHITE);

///////////////////////////////







  // 初始化自定义SPI通信，传入SCK、MISO、MOSI引脚及CS控制信号
  CustomSPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS);

  // 等待直到串口完全初始化
  while (!Serial)
  {
    ;
  } 

  // 打印初始化SD卡的开始信息
  Serial.println("Initializing SD card...");
  
  // 初始化SD卡，如果初始化失败则打印错误信息并返回
  if (!SD.begin(CS, CustomSPI, 1000000))
  {
    Serial.println("initialization failed!");
    return;
  }
  
  // 打印SD卡初始化成功的消息
  Serial.println("initialization done.");

  // 写入测试文件"/test.txt"
  WriteFile("/txt4.txt", "hello worlD");
  
  // 读取测试文件"/test.txt"的内容

  //打印读取到的内容
  Serial.println("Reading from test.txt");
  //Serial.println(picTxt);

  //createDir(SD,"/mydir");

  
//  listDir(SD,"/sys/Picture/data",3);
//  for (int index = 0;index<fileIndex;index++){
//      Serial.println("/sys/Picture/data/"+fileList[index]);
//      String picTxt =ReadFile_txt((char*)("/sys/Picture/data/"+fileList[index]).c_str());
//      base64::decode((char*) picTxt.c_str(), frame_0);
//      TJpgDec.drawJpg( 0, 0,frame_0, sizeof(frame_0));
//    }


  tft.fillScreen(TFT_WHITE);
  listDir(SD,"/sys",1);
  for (int index = 0;index<dirIndex;index++){
      Serial.println("/sys/"+dirList[index]);
//      tft.setFreeFont(FF22);                 // Select the font
//      tft.setTextColor(TFT_BLACK, TFT_WHITE);
//      tft.drawString(dirList[index] ,2*w/3-5, 35*index +40, GFXFF);
      page[index] = dirList[index] ;

    }
  pRanderPage = renderMenuPage;
  pRanderPage(0);
//  String picTxt =ReadFile_txt("/sys/Picture/icon.txt");
//  base64::decode((char*) picTxt.c_str(), frame_0);
//  TJpgDec.drawJpg( 0, 0,frame_0, sizeof(frame_0));
}




void loop()
{
  runOS();
  
}

void plotMap(){
  
  for(int i = 0;i<16;i++){
    for(int j = 0;j<3;j++){
      Serial.print(OSIndexMap[i][j]);
      }
    Serial.println();
    
    }
  }

void runOS(){



            if (clickB()) {
                clickB_push_count = clickB_push_count+1;
                if (clickB_push_count==2){ //短按
                  //clickB_once_count +=1;
                  Serial.println("clickB Click");
                  OSIndexMap[OSIndexX][OSIndexY]=0;
                  OSIndexX+=1;
                  if (OSIndexX>15) OSIndexX=0;
                  OSIndexMap[OSIndexX][OSIndexY]=1;
                  plotMap();
                  
                  pRanderPage(OSIndexX);
                  Serial.println(dirList[OSIndexX]);
                 
                  }     
                if (clickB_push_count==1000){//长按
                  //clickB_once_count -=2;
                  Serial.println("clickB Push");
                  pRanderPage = renderBookPage;
                  pRanderPage(OSIndexX);
                  }
                
              }
           else{
             clickB_push_count = 1;}
                   
           if (clickC()) {
                clickC_push_count = clickC_push_count+1;
                if (clickC_push_count==2){ //短按
                  //clickC_once_count +=1;
                  Serial.println("clickC Click");
                  OSIndexMap[OSIndexX][OSIndexY]=0;
                  OSIndexX-=1;
                  if (OSIndexX<0) OSIndexX=15;
                  OSIndexMap[OSIndexX][OSIndexY]=1;
                  plotMap();
                  //pRanderPage = renderMenuPage;
                  pRanderPage(OSIndexX);
                  Serial.println(dirList[OSIndexX]);
                  
                  }     
                if (clickC_push_count==1000){//长按
                  //clickC_once_count -=2;
                  Serial.println("clickC Push");
                  pRanderPage = renderMenuPage;
                  pRanderPage(OSIndexX);
                  }
                
              }
            else{
               clickC_push_count = 1;}  

         
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

int renderMenuPage(int index){
 //tft.fillScreen(TFT_WHITE);
 tft.fillRect(0, 0 , 120 , 240, TFT_WHITE);
 //tft.fillRect(120, 0 , 120 , 240, YELLOW);
 tft.fillRoundRect(120, 0, 120, 240, 16, YELLOW);
//tft.fillRect(225, 40 , 2 , 190, TFT_WHITE);//bar
//tft.fillRect(225-8, 40 , 8 , 20, TFT_WHITE);//bar
              //x  y  dx  dy 

 
// String page[] = {"Video.","Music.","Game.","Image.","MSG.","Setting."};


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
   
   for (int t=0;t<20;t++){
     if (t==0){
     String sysPath = "/sys/";
     String APPicon = "/icon.txt";
     String APPpath = dirList[OSIndexX];
     String picTxt =ReadFile_txt((sysPath+APPpath+APPicon).c_str());
     base64::decode((char*) picTxt.c_str(), frame_0);}
     TJpgDec.drawJpg(  t-0, 120-50,frame_0, sizeof(frame_0));
   }

//
//          if(index==0){
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon1a[0], icon1a_size[0], t-10, 120-50); }
//          if(index==1){
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon2a[0], icon2a_size[0], t-10, 120-50); }
//          if(index==2){
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon3a[0], icon3a_size[0], t-10, 120-50); }
//          if(index==3){   
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon4a[0], icon4a_size[0], t-10, 120-50); }
//          if(index==4){   
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon5a[0], icon5a_size[0], t-10, 120-50); }
//          if(index==5){   
//          for (int t=0;t<20;t++)
//          drawArrayJpeg(icon6a[0], icon6a_size[0], t-10, 120-50); }




  return 0;
  }


 int renderBookPage(int index){
    tft.fillScreen(TFT_BLACK);
    String bookTxt =ReadFile_txt("/sys/Books/data/book1.txt");
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(bookTxt,0, 0, GFXFF);
    
    return 0;
  }
