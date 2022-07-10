#include <WiFi.h> //wifi库
#include <ArduinoJson.h>  //Json库
#include <HTTPClient.h>  //HTTP库
//const char* ssid = "Xiaomi_2304";
//const char* password = "15300786298";
const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

const char* host = "192.168.43.48";  //心知天气服务器地址
String now_address="",now_time="",now_temperature="";//用来存储报文得到的字符串



//////////////////



// New background colour
#define TFT_BROWN 0x38E0

// Pause in milliseconds between screens, change to 0 to time font rendering
#define WAIT 500

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h









/////////////////
void setup()
{
  /////////////
  tft.init();
  tft.setRotation(1);
  
////////////////////

  
  Serial.begin(115200);
  // 连接网络
  WiFi.begin(ssid, password);
  //等待wifi连接
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); //连接成功
  Serial.print("IP address: ");    //打印IP地址
  Serial.println(WiFi.localIP());
}
void loop()
{






  
    //创建TCP连接
    WiFiClient client;
    const int httpPort = 5000;
    if (!client.connect(host, httpPort))
    {
      Serial.println("connection failed");  //网络请求无响应打印连接失败
      return;
    }
    //URL请求地址
    //String url ="/v3/weather/now.json?key=SeAeuMjbRTJo4I_ZN&location=shanghai&language=zh-Hans&unit=c";
    String url ="/index";
    //发送网络请求
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
              "Host: " + host + "\r\n" +
              "Connection: close\r\n\r\n");
    delay(5000);
    //定义answer变量用来存放请求网络服务器后返回的数据
    String answer;
    while(client.available())
    {
      String line = client.readStringUntil('\r');
      answer += line;
    }
    //断开服务器连接
  client.stop();
  Serial.println();
  Serial.println("closing connection");
//获得json格式的数据
  String jsonAnswer;
  int jsonIndex;
  //找到有用的返回数据位置i 返回头不要
  for (int i = 0; i < answer.length(); i++) {
    if (answer[i] == '{') {
      jsonIndex = i;
      break;
    }
  }
  jsonAnswer = answer.substring(jsonIndex);
  Serial.println();
  Serial.println("JSON answer: ");
  Serial.println(jsonAnswer);


// Stream& input;

StaticJsonDocument<256> doc;

DeserializationError error = deserializeJson(doc, jsonAnswer);

if (error) {
  Serial.print("deserializeJson() failed: ");
  Serial.println(error.c_str());
  return;
}

const char* name = doc["name"]; // "Everyone is a genius. But if you judge a fish by its ability to ...
int number = doc["number"]; // 18


///////////////////

  // 设置起始坐标(20, 10)，4 号字体
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(0, 0);
  // 设置文本颜色为白色，黑色文本背景
  tft.setTextFont(number);
  tft.setTextColor( TFT_BLACK,TFT_WHITE);
  // 设置显示的文字，注意这里有个换行符 \n 产生的效果
  tft.println(name);

 

/////////////////




  
}
