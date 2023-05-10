/*
 LEDC Software Fade

 This example shows how to software fade LED
 using the ledcWrite function.

 Code adapted from original Arduino Fade example:
 https://www.arduino.cc/en/Tutorial/Fade

 This example code is in the public domain.
 */
  void str2pic(String PictInfo)
  {
  
  String numString[9] ={"","","","","","","","",""};
  int numInt[9];
  int numIndex = 0;
  for (int i=0;i<PictInfo.length();i++){
    if(PictInfo[i]!=',')
    numString[numIndex] += PictInfo[i];
    else{
      numIndex++;
      }
    }
  uint8_t pic_uint8_t_0[] PROGMEM = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
  const uint8_t *pic_uint8_t[1] PROGMEM { pic_uint8_t_0,};
  const uint32_t pic_uint8_t_size[1] PROGMEM { 9,};

  
  for (int i=0;i<9;i++){
    
    numInt[i]=numString[i].toInt();
    pic_uint8_t_0[i] = (uint8_t)numInt[i];
    Serial.println(numInt[i]);
    
    }
  }

  


void setup() {
  Serial.begin(9600);
  // Setup timer and attach timer to a led pin



 
  
  String PictInfo="1,23,3,4,5,5,50,100,200";
  str2pic( PictInfo);

  
}

void loop() {
  
  delay(30);
}
