// Example for library:
// https://github.com/Bodmer/TJpg_Decoder

// This example renders a Jpeg file that is stored in an array within Flash (program) memory
// see panda.h tab.  The panda image file being ~13Kbytes.

// Include the array
#include "panda.h"

// Include the jpeg decoder library
#include <TJpg_Decoder.h>

// Include the TFT library https://github.com/Bodmer/TFT_eSPI
#include "SPI.h"
#include <TFT_eSPI.h>              // Hardware-specific library
TFT_eSPI tft = TFT_eSPI();         // Invoke custom library

#include "icon_1_1.h"
#include "icon_1_2.h"
#include "icon_1_3.h"
#include "icon_1_4.h"



// This next function will be called during decoding of the jpeg file to
// render each block to the TFT.  If you use a different TFT library
// you will need to adapt this function to suit.
bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)
{
   // Stop further decoding as image is running off bottom of screen
  if ( y >= tft.height() ) return 0;

  // This function will clip the image block rendering automatically at the TFT boundaries
  tft.pushImage(x, y, w, h, bitmap);

  // This might work instead if you adapt the sketch to use the Adafruit_GFX library
  // tft.drawRGBBitmap(x, y, bitmap, w, h);

  // Return 1 to decode next block
  return 1;
}

void setup()
{

  Serial.begin(115200);
  Serial.println("\n\n Testing TJpg_Decoder library");

  // Initialise the TFT
  tft.begin();
  tft.setTextColor(0xFFFF, 0x0000);
  tft.fillScreen(TFT_BLACK);

  // The jpeg image can be scaled by a factor of 1, 2, 4, or 8
  TJpgDec.setJpgScale(1);

  // The byte order can be swapped (set true for TFT_eSPI)
  TJpgDec.setSwapBytes(true);

  // The decoder must be given the exact name of the rendering function above
  TJpgDec.setCallback(tft_output);
}

void loop()
{
  tft.fillScreen(TFT_WHITE);

  int speed = int(5);

  for (int i=0;i<=int(3*240/speed);i++){
    TJpgDec.drawJpg( 60+i*speed, 60,icon_1_1_0, icon_1_1_size[0]); // Draw a jpeg image stored in memory at x,y
    delay(2);
    TJpgDec.drawJpg( 60-240+i*speed, 60,icon_1_2_0, icon_1_2_size[0]); // Draw a jpeg image stored in memory
    delay(2);
    TJpgDec.drawJpg( 60-240*2+i*speed, 60,icon_1_3_0, icon_1_3_size[0]); // Draw a jpeg image stored in memory
    delay(2);
    TJpgDec.drawJpg( 60-240*3+i*speed, 60,icon_1_4_0, icon_1_4_size[0]); // Draw a jpeg image stored in memory
  }



}
