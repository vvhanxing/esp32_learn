#include <WiFi.h>
#include <WebServer.h>


const char* ssid = "HUAWEI P50 Pro";  // Enter your SSID here
const char* password = "12345678";  //Enter your Password here

WebServer server(80);

void setup(){
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while(WiFi.status() !=WL_CONNECTED){
    delay(500);
    Serial.println(".");
  }
  
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    server.begin();
    server.on("/",HTTP_GET, handleRoot);      //服务器首页
    server.on("/led",HTTP_POST,handleled );    //led控制页
    server.onNotFound(handleNotFound);      //404页面

    Serial.print("HTTP server started");
    
}

void loop(void){
  server.handleClient();
 }

void handleRoot(){
  server.send(200, "text/html", "<form action=\"/led\" method=\"POST\"> <input type=\"submit\" value=\"button\"></form>");
}

void handleled(){
  //控制led状态并返回至首页
  digitalWrite(LED_BUILTIN,!digitalRead(LED_BUILTIN));
  server.sendHeader("Location","/");
  server.send(303);
  }

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}
