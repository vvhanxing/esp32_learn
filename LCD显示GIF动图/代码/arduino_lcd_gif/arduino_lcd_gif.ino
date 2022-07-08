#include <SPI.h>
#include <TFT_eSPI.h>
#include <AnimatedGIF.h>
// #include "Arduino.h"
// #include <esp_heap_caps.h>

#include "gif_demo1.h"
//#include "gif_demo2.h"
#include "gif_demo3.h"
#include "gif_demo4.h"
//#include "gif_demo5.h"

#define GIF_DEMO1 gif_demo1
//#define GIF_DEMO2 gif_demo2
#define GIF_DEMO3 gif_demo3
#define GIF_DEMO4 gif_demo4
//#define GIF_DEMO5 gif_demo5

#ifdef ESP8266
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

AnimatedGIF gif;
TFT_eSPI tft = TFT_eSPI();

#define GIF_ENABLE
#define NORMAL_SPEED    // Comment out for rame rate for render speed test

#ifdef GIF_ENABLE
// GIFDraw is called by AnimatedGIF library frame to screen
#define DISPLAY_WIDTH  tft.width()
#define DISPLAY_HEIGHT tft.height()
#define BUFFER_SIZE 256            // Optimum is >= GIF width or integral division of width

#ifdef USE_DMA
  uint16_t usTemp[2][BUFFER_SIZE]; // Global to support DMA use
#else
  uint16_t usTemp[1][BUFFER_SIZE];    // Global to support DMA use
#endif
bool     dmaBuf = 0;

// Draw a line of image directly on the LCD
void GIFDraw(GIFDRAW *pDraw)
{
  uint8_t *s;
  uint16_t *d, *usPalette;
  int x, y, iWidth, iCount;

  // pDraw->iX = 50;
  // pDraw->iY = 50;

  // Displ;ay bounds chech and cropping
  iWidth = pDraw->iWidth;
  if (iWidth + pDraw->iX > DISPLAY_WIDTH)
    iWidth = DISPLAY_WIDTH - pDraw->iX;
  usPalette = pDraw->pPalette;
  y = pDraw->iY + pDraw->y; // current line
  if (y >= DISPLAY_HEIGHT || pDraw->iX >= DISPLAY_WIDTH || iWidth < 1)
    return;

  // Old image disposal
  s = pDraw->pPixels;
  if (pDraw->ucDisposalMethod == 2) // restore to background color
  {
    for (x = 0; x < iWidth; x++)
    {
      if (s[x] == pDraw->ucTransparent)
        s[x] = pDraw->ucBackground;
    }
    pDraw->ucHasTransparency = 0;
  }

  // Apply the new pixels to the main image
  if (pDraw->ucHasTransparency) // if transparency used
  {
    uint8_t *pEnd, c, ucTransparent = pDraw->ucTransparent;
    pEnd = s + iWidth;
    x = 0;
    iCount = 0; // count non-transparent pixels
    while (x < iWidth)
    {
      c = ucTransparent - 1;
      d = &usTemp[0][0];
      while (c != ucTransparent && s < pEnd && iCount < BUFFER_SIZE )
      {
        c = *s++;
        if (c == ucTransparent) // done, stop
        {
          s--; // back up to treat it like transparent
        }
        else // opaque
        {
          *d++ = usPalette[c];
          iCount++;
        }
      } // while looking for opaque pixels
      if (iCount) // any opaque pixels?
      {
        // DMA would degrtade performance here due to short line segments
        tft.setAddrWindow(pDraw->iX + x, y, iCount, 1);
        tft.pushPixels(usTemp, iCount);
        x += iCount;
        iCount = 0;
      }
      // no, look for a run of transparent pixels
      c = ucTransparent;
      while (c == ucTransparent && s < pEnd)
      {
        c = *s++;
        if (c == ucTransparent)
          x++;
        else
          s--;
      }
    }
  }
  else
  {
    s = pDraw->pPixels;

    // Unroll the first pass to boost DMA performance
    // Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
    if (iWidth <= BUFFER_SIZE)
      for (iCount = 0; iCount < iWidth; iCount++) usTemp[dmaBuf][iCount] = usPalette[*s++];
    else
      for (iCount = 0; iCount < BUFFER_SIZE; iCount++) usTemp[dmaBuf][iCount] = usPalette[*s++];

#ifdef USE_DMA // 71.6 fps (ST7796 84.5 fps)
    tft.dmaWait();
    tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
    tft.pushPixelsDMA(&usTemp[dmaBuf][0], iCount);
    dmaBuf = !dmaBuf;
#else // 57.0 fps
    tft.setAddrWindow(pDraw->iX, y, iWidth, 1);
    tft.pushPixels(&usTemp[0][0], iCount);
#endif

    iWidth -= iCount;
    // Loop if pixel buffer smaller than width
    while (iWidth > 0)
    {
      // Translate the 8-bit pixels through the RGB565 palette (already byte reversed)
      if (iWidth <= BUFFER_SIZE)
        for (iCount = 0; iCount < iWidth; iCount++) usTemp[dmaBuf][iCount] = usPalette[*s++];
      else
        for (iCount = 0; iCount < BUFFER_SIZE; iCount++) usTemp[dmaBuf][iCount] = usPalette[*s++];

#ifdef USE_DMA
      tft.dmaWait();
      tft.pushPixelsDMA(&usTemp[dmaBuf][0], iCount);
      dmaBuf = !dmaBuf;
#else
      tft.pushPixels(&usTemp[0][0], iCount);
#endif
      iWidth -= iCount;
    }
  }
} /* GIFDraw() */
#endif

void setup() 
{
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(2);
    tft.fillScreen(TFT_BLACK);

    gif.begin(BIG_ENDIAN_PIXELS);
}

#ifdef NORMAL_SPEED // Render at rate that is GIF controlled
void loop()
{
#ifdef GIF_DEMO1
    if (gif.open((uint8_t *)GIF_DEMO1, sizeof(GIF_DEMO1), GIFDraw))
    {
      Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
#endif
//
//#ifdef GIF_DEMO2
//    if (gif.open((uint8_t *)GIF_DEMO2, sizeof(GIF_DEMO2), GIFDraw))
//    {
//      Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
//      tft.startWrite(); // The TFT chip slect is locked low
//      while (gif.playFrame(true, NULL))
//      {
//        yield();
//      }
//      gif.close();
//      tft.endWrite(); // Release TFT chip select for other SPI devices
//    }
//#endif

#ifdef GIF_DEMO3
    if (gif.open((uint8_t *)GIF_DEMO3, sizeof(GIF_DEMO3), GIFDraw))
    {
      Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
#endif

  #ifdef GIF_DEMO4
    if (gif.open((uint8_t *)GIF_DEMO4, sizeof(GIF_DEMO4), GIFDraw))
    {
      tft.fillScreen(TFT_BLACK);
      Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
      tft.startWrite(); // The TFT chip slect is locked low
      while (gif.playFrame(true, NULL))
      {
        yield();
      }
      gif.close();
      tft.endWrite(); // Release TFT chip select for other SPI devices
    }
  #endif

//#ifdef GIF_DEMO5
//    if (gif.open((uint8_t *)GIF_DEMO5, sizeof(GIF_DEMO5), GIFDraw))
//    {
//      Serial.printf("Successfully opened GIF; Canvas size = %d x %d\n", gif.getCanvasWidth(), gif.getCanvasHeight());
//      tft.startWrite(); // The TFT chip slect is locked low
//      while (gif.playFrame(true, NULL))
//      {
//        yield();
//      }
//      gif.close();
//      tft.endWrite(); // Release TFT chip select for other SPI devices
//    }
//#endif
}
#else // Test maximum rendering speed
void loop()
{
    long lTime = micros();
    int iFrames = 0;

    if (gif.open((uint8_t *)GIF_DEMO4, sizeof(GIF_DEMO4), GIFDraw))
    {
        tft.startWrite(); // For DMA the TFT chip slect is locked low
        while (gif.playFrame(false, NULL))
        {
            // Each loop renders one frame
            iFrames++;
            yield();
        }
        gif.close();
        tft.endWrite(); // Release TFT chip select for other SPI devices
        lTime = micros() - lTime;
        Serial.print(iFrames / (lTime / 1000000.0));
        Serial.println(" fps");
    }
}
#endif
