#include <Arduino.h>

#include "AudioFileSourcePROGMEM.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2SNoDAC.h"

// VIOLA sample taken from https://ccrma.stanford.edu/~jos/pasp/Sound_Examples.html
#include "viola.h"

AudioGeneratorWAV *wav;
AudioFileSourcePROGMEM *file;
AudioOutputI2SNoDAC *out;

void initvideo(){

  Serial.println("M1");
  audioLogger = &Serial;
  Serial.println("M2");
  file = new AudioFileSourcePROGMEM( viola, sizeof(viola) );
  Serial.println("M3");  
  out = new AudioOutputI2SNoDAC();
  Serial.println("M4");  
  wav = new AudioGeneratorWAV();
  Serial.println("M5");  
  wav->begin(file, out);
  Serial.println("M6");   
  
  
  }


void setup()
{
  Serial.begin(9600);
  delay(1000);
  Serial.printf("WAV start\n");
  initvideo();

}

void loop()
{
  if (wav->isRunning()) {
    if (!wav->loop()) wav->stop();
  } else {
    Serial.printf("WAV done\n");
    delay(1000);
  }
}
