#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>

#include <uri/UriBraces.h>
#include <uri/UriRegex.h>

const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

//

#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h




String info="hello vivi";
//

///////////////////
void screenInfo(String info){
  // 设置起始坐标(20, 10)，4 号字体
  tft.fillScreen(TFT_WHITE);
  tft.setCursor(0, 0);
  // 设置文本颜色为白色，黑色文本背景
  tft.setTextFont(4);
  tft.setTextColor( TFT_BLACK,TFT_WHITE);
  // 设置显示的文字，注意这里有个换行符 \n 产生的效果
  tft.println(info);

/////////////////  
  
  }


WebServer server(80);


void getInfo(){
  info = server.arg("info") ;
  screenInfo(info);
  server.sendHeader("Location","/info");
  server.send(302,"text/plain","ok");
  }


void putInfo(){
  server.send(200,"text/html",(String)"<!DOCTYPE html><body><h1>"+info+"</h1></body></html>");
 
  }

  
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

void runServer(){
  initServer();
  //server.on(F("/"), []() {
    //server.send(200, "text/plain", "hello from esp32!");
  //});

  server.on("/info",HTTP_GET,putInfo);
  server.on("/info",HTTP_POST,getInfo);
  
  server.begin();
  Serial.println("HTTP server started");

  
  }



void setup(void) {
  Serial.begin(9600);
  runServer();
  

  tft.init();
  tft.setRotation(1);
  screenInfo(info);

}

void loop(void) {
  server.handleClient();
  delay(400);//allow the cpu to switch to other tasks





  
}
