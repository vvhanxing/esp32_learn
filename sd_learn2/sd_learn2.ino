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

// 定义一个文件对象
File myFile; 

const int CS = 22; // 定义SPI通信中CS（Chip Select）信号的常量
const int MOSI_PIN = 17; // 定义SPI通信中MOSI（Master Out Slave In）信号的常量
const int MISO_PIN = 2; // 定义SPI通信中MISO（Master In Slave Out）信号的常量
const int SCK_PIN = 16; // 定义SPI通信中SCK（Serial Clock）信号的常量

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


void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
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
void ReadFile(const char *path)
{
  myFile = SD.open(path); // 尝试打开文件
  
  if (myFile) // 如果文件成功打开
  {
    Serial.printf("Reading file from %s\n", path); // 打印读取文件的路径信息
    while (myFile.available()) // 循环读取文件中的所有内容
    {
      Serial.write(myFile.read()); // 将读取到的每个字节通过串口发送
    }
    myFile.close(); // 关闭文件
  }
  else // 如果文件打开失败
  {
    Serial.println("error opening test.txt"); // 打印错误信息
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
void setup()
{
  // 初始化串口通信，设置波特率为9600，并延迟500ms
  Serial.begin(9600);
  delay(500);

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
  ReadFile("/test.txt");
  //打印读取到的内容
  Serial.println("Reading from test.txt");

  //createDir(SD,"/mydir");
  listDir(SD,"/mydir",1);

}

void loop()
{

}
