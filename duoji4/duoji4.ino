#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <ESP32Servo.h>

// WiFi credentials
const char* ssid = "HUAWEI P50 Pro";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

// Define the four servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Define servo pins
const int servoPin1 = 13;
const int servoPin2 = 27;
const int servoPin3 = 14;
const int servoPin4 = 12;

//
// HTML content for the control page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML>
<html>
<head>
  <title>Robot Dog Control</title>
  <style>
    button {
      width: 100px;
      height: 50px;
      font-size: 20px;
      margin: 10px;
    }
  </style>
</head>
<body>
  <h1>Robot Dog Control</h1>
  <button onclick="sendCommand('forward')">Forward</button>
  <button onclick="sendCommand('backward')">Backward</button>
  <button onclick="sendCommand('left')">Left</button>
  <button onclick="sendCommand('right')">Right</button>
  <button onclick="sendCommand('stand')">Stand</button>
  <button onclick="sendCommand('sit')">Sit</button>
  <button onclick="sendCommand('shake')">Shake</button>
   <button onclick="sendCommand('sleep')">Sleep</button>

  <script>
    function sendCommand(command) {
      fetch('/' + command)
        .then(response => response.text())
        .then(data => console.log(data));
    }
  </script>
</body>
</html>
)rawliteral";

//
String Action = "TaskStand";

void setup() {
  // Initialize serial monitor
  Serial.begin(115200);

  // Attach the servos to the defined pins
  servo1.attach(servoPin1);
  servo2.attach(servoPin2);
  servo3.attach(servoPin3);
  servo4.attach(servoPin4);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  
  Serial.println("Connected to WiFi");

  // Initialize the HTTP server routes
 

   server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  }); 

  server.on("/forward", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskForward";
    request->send(200, "text/plain", "Moving Forward");
  });

  server.on("/backward", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskBackward";
    request->send(200, "text/plain", "Moving Backward");
  });

  server.on("/left", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskLeft";
    request->send(200, "text/plain", "Moving Left");
  });

  server.on("/right", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskRight";
    request->send(200, "text/plain", "Moving Right");
  });

  server.on("/stand", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskStand";
    request->send(200, "text/plain", "Standing");
  });

  server.on("/sit", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskSit";
    request->send(200, "text/plain", "Sitting");
  });

  server.on("/shake", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskShake";
    request->send(200, "text/plain", "Shaking");
  });

  server.on("/sleep", HTTP_GET, [](AsyncWebServerRequest *request){
    Action = "TaskSleep";
    request->send(200, "text/plain", "Sleeping");
  });

  // Start server
  server.begin();
}

void loop() {
  // The loop function is empty as we are using freeRTOS tasks
  if (Action=="TaskForward") taskForward();
  if (Action=="TaskBackward") taskBackward();
  if (Action=="TaskLeft") taskLeft();
  if (Action=="TaskRight") taskRight();
  if (Action=="TaskStand") taskStand();
  if (Action=="TaskSit") taskSit();
  if (Action=="TaskShake") taskShake();
  if (Action=="TaskSleep") taskSleep();
//  taskForward();


 
  
}

// Define the tasks
void taskForward() {
    // Define the forward motion for the servos
    Serial.println("forward motion");
    servo1.write(50);  // Example angles, adjust as needed
    delay(200); 
    servo2.write(130);
    delay(200);
    servo3.write(50);
    delay(200);
    servo4.write(130);
    delay(200);  // Adjust delay as needed for smoother movement
    servo1.write(130);  // Example angles, adjust as needed
    delay(200);
    servo2.write(50);
    delay(200);
    servo3.write(130);
    delay(200);
    servo4.write(50);
    delay(200);

}

void taskBackward() {
    Serial.println("backward motion");
    servo4.write(50);  // Example angles, adjust as needed
    delay(200); 
    servo3.write(130);
    delay(200);
    servo2.write(50);
    delay(200);
    servo1.write(130);
    delay(200);  // Adjust delay as needed for smoother movement
    servo4.write(130);  // Example angles, adjust as needed
    delay(200);
    servo3.write(50);
    delay(200);
    servo2.write(130);
    delay(200);
    servo1.write(50);
    delay(200);

}

void taskLeft() {

    // Define the left motion for the servos
    Serial.println("left motion");
    servo1.write(60);  // Example angles, adjust as needed
    delay(100); 
    servo4.write(120);
    delay(100);
    servo3.write(60);
    delay(100);
    servo2.write(120);
    delay(100);  // Adjust delay as needed for smoother movement
    servo1.write(120);  // Example angles, adjust as needed
    delay(100);
    servo4.write(60);
    delay(100);
    servo3.write(120);
    delay(100);
    servo2.write(60);
    delay(100);
 
}

void taskRight() {
    Serial.println("right motion");

    // Define the right motion for the servos

    // Define the left motion for the servos
    Serial.println("left motion");
    servo3.write(60);  // Example angles, adjust as needed
    delay(100); 
    servo4.write(120);
    delay(100);
    servo1.write(60);
    delay(100);
    servo2.write(120);
    delay(100);  // Adjust delay as needed for smoother movement
    servo3.write(120);  // Example angles, adjust as needed
    delay(100);
    servo4.write(60);
    delay(100);
    servo1.write(120);
    delay(100);
    servo2.write(60);
    delay(100);
  
}

void taskStand() {
    Serial.println("standing motion");
    // Define the standing motion for the servos
    servo1.write(90);  // Example angles, adjust as needed
    delay(100);
    servo2.write(90);
    delay(100);
    servo3.write(90);
    delay(100);
    servo4.write(90);
    delay(100);  // Adjust delay as needed for smoother movement

}

void taskSit() {
    Serial.println("sitting motion");
    // Define the sitting motion for the servos
    servo1.write(90);  // Example angles, adjust as needed
    delay(100);
    servo2.write(160);
    delay(100);
    servo3.write(90);
    delay(100);
    servo4.write(20);
    delay(100);  // Adjust delay as needed for smoother movement
}


//taskSleep

void taskSleep() {
    Serial.println("sleeping motion");
    // Define the sitting motion for the servos
    servo1.write(0);  // Example angles, adjust as needed
    delay(100);
    servo2.write(0);
    delay(100);
    servo3.write(180);
    delay(100);
    servo4.write(180);
    delay(100);  // Adjust delay as needed for smoother movement
}


void taskShake() {
    Serial.println("shaking motion");
    // Define the shaking motion for the servos
    servo1.write(30);  // Example angles, adjust as needed
    delay(100);
    servo1.write(0);  // Example angles, adjust as needed
    delay(100);
    servo2.write(160);
    delay(100);
    servo3.write(90);
    delay(100);
    servo4.write(20);
    delay(100);  // Adjust delay as needed for smoother movement
  
}
