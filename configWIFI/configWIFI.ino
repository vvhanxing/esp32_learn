#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

const char* ssid = "ESP32";  // SoftAP的SSID
const char* password = "12345678";        // SoftAP的密码

WebServer server(80);  // 创建Web服务器对象
DNSServer dnsServer;   // 创建DNS服务器对象
int isConnectedWIFI =0;
const char* htmlPage = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 WiFi Configuration</title>
  </head>
  <body>
    <h1>ESP32 WiFi Configuration</h1>
    <form action="/config" method="post">
      <label for="ssid">SSID:</label><br>
      <input type="text" id="ssid" name="ssid"><br>
      <label for="password">Password:</label><br>
      <input type="password" id="password" name="password"><br><br>
      <input type="submit" value="Submit">
    </form>
  </body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  dnsServer.start(53, "*", WiFi.softAPIP());

  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", htmlPage);
  });

  server.on("/config", HTTP_POST, []() {
    String ssid = server.arg("ssid");
    String password = server.arg("password");
    String response = "SSID: " + ssid + "<br>Password: " + password;
    server.send(200, "text/html", response);
    delay(1000);
    connectToWiFi(ssid.c_str(), password.c_str());
  });

  server.begin();
  Serial.println("HTTP server started");
}

void connectToWiFi(const char* ssid, const char* password) {
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  isConnectedWIFI=1;
}

void loop() {
  if (isConnectedWIFI==0){
  dnsServer.processNextRequest();
  server.handleClient();}
  else {
    Serial.println(" start do something");
    delay(1000);
  }
}
