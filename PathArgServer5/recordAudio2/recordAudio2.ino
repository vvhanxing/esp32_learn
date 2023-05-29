/*
 * Uses a MAX4466 microphone to take samples
 * The mic must use a seperate power supply (3.3v or 5v) as the ESP32 has too much noise on power lines
 * Data Received by a C++ program which saves the data in a file
 * File can be opened in Audacity as unsigned 8 bit PCM, endianess makes no difference, and played at a speed of 11,025hz (roughly)
 * 
 */
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>



const char* ssid = "HUAWEI P50 Pro";
const char* password = "12345678";
const char* serverAddress = "http://192.168.43.185:5000/upload/";
const int serverPort = 5000;


const int sampleWindow = 50;  // Sample window width in milliseconds
unsigned int sampleRate = 44100;  // ADC sampling rate
unsigned long lastSampleTime = 0;

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize ADC
  analogReadResolution(12);  // 12-bit ADC resolution (0-4095)
  analogSetWidth(12);

  // Set ADC attenuation
  analogSetAttenuation(ADC_11db);  // Set 11 dB attenuation for maximum voltage range

  // Wait for stabilization of ADC reference voltage
  delay(1000);
}

void loop() {
  // Check if it's time to take a sample
  if (millis() - lastSampleTime >= sampleWindow) {
    lastSampleTime += sampleWindow;

    // Read ADC value
    int sensorValue = analogRead(A0);

    // Convert ADC value to voltage
    float voltage = sensorValue * 3.3 / 4095.0;

    // Send voltage value to server
    sendVoltage(voltage);
  }
}

void sendVoltage(float voltage) {
  WiFiClient client;
  HTTPClient http;

  // Construct URL for the HTTP POST request
  String url = "http://" + String(serverAddress) + ":" + String(serverPort) + "/upload";
  
  // Send the POST request with the voltage value as a parameter
  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  int httpResponseCode = http.POST("voltage=" + String(voltage));
  String response = http.getString();

  // Print the response from the server
  Serial.println("Response code: " + String(httpResponseCode));
  Serial.println("Response: " + response);

  http.end();
}
