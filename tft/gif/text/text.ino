#include <SPI.h> //导入库
#include <TFT_eSPI.h>   

#include "a.h"    //导入图库
TFT_eSPI tft = TFT_eSPI(); 
int i=0;
void setup()
{
  tft.init();    //初始化
  tft.fillScreen(TFT_BLACK);//屏幕颜色
  //tft.setRotation(4);//镜像显示
}
void loop()
{
  tft.pushImage(0, 0,   240,240, imgArraya);//调用图片数据
  //i+=1;
  //if(i>9){i=0;}
  //delay(100);
}
