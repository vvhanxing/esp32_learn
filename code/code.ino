/*
  ledcWrite_RGB.ino
  Runs through the full 255 color spectrum for an rgb led 
  Demonstrate ledcWrite functionality for driving leds with PWM on ESP32
 
  This example code is in the public domain.
  
  Some basic modifications were made by vseven, mostly commenting.
 */
 
// Set up the rgb led names
uint8_t ledR = 2;
uint8_t ledG = 4;
uint8_t ledB = 5; 

uint8_t ledArray[3] = {1, 2, 3}; // three led channels

const boolean invert = true; // set true if common anode, false if common cathode

uint8_t color = 0;          // a value from 0 to 255 representing the hue
uint32_t R, G, B;           // the Red Green and Blue color components
uint8_t brightness = 255;  // 255 is maximum brightness, but can be changed.  Might need 256 for common anode to fully turn off.

// the setup routine runs once when you press reset:
void setup() 
{            
  Serial.begin(115200);
  delay(10); 

}

// void loop runs over and over again
void loop() 
{


  Serial.println("Send all LEDs a 0 and wait 2 seconds.");
 
  delay(2000);
  const uint8_t a2_0[] PROGMEM = { 0xff, 0xd8, 0xff, 0xe0, 0x00 };
  for (int i = 0;i<3;i++){
    Serial.println(a2_0[i]);
    }

}
