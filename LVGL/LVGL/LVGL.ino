/**
* @name:liuzewen
* @title:lvgl_test
* @time:2020/8/14
*/
#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>
#include <SPI.h>
#include <TFT_Touch.h>

#define LVGL_TICK_PERIOD 60

TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

lv_obj_t * slider_label;
int screenWidth = 480;
int screenHeight = 320;

//触摸
#define DOUT 14  /* Data out pin (T_DO) of touch screen */
#define DIN  27  /* Data in pin (T_DIN) of touch screen */
#define DCS  26  /* Chip select pin (T_CS) of touch screen */
#define DCLK 25  /* Clock pin (T_CLK) of touch screen */
TFT_Touch touch = TFT_Touch(DCS, DCLK, DIN, DOUT);
int X_Raw = 0, Y_Raw = 0;

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char * file, uint32_t line, const char * dsc)
{

  Serial.printf("%s@%d->%s\r\n", file, line, dsc);
  delay(100);
}
#endif

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint16_t c;

  tft.startWrite(); /* Start new TFT transaction */
  tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
  for (int y = area->y1; y <= area->y2; y++) {
    for (int x = area->x1; x <= area->x2; x++) {
      c = color_p->full;
      tft.writeColor(c, 1);
      color_p++;
    }
  }
  tft.endWrite(); /* terminate TFT transaction */
  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool my_touchpad_read(lv_indev_drv_t * indev_driver, lv_indev_data_t * data)
{
    uint16_t touchX, touchY;

    bool touched = touch.Pressed();//检测触摸是否按下
    //获取屏幕坐标
    touchX = touch.X();
    touchY = touch.Y();

    if(!touched)
    {
      return false;
    }

    if(touchX>screenWidth || touchY > screenHeight)
    {
      Serial.println("Y or y outside of expected parameters..");
      Serial.print("y:");
      Serial.print(touchX);
      Serial.print(" x:");
      Serial.print(touchY);
    }
    else
    {

      data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL; 
  
      /*Save the state and save the pressed coordinate*/
      //if(data->state == LV_INDEV_STATE_PR) touchpad_get_xy(&last_x, &last_y);
     
      /*Set the coordinates (if released use the last pressed coordinates)*/
      data->point.x = touchX;
      data->point.y = touchY;
  
      Serial.print("Data x");
      Serial.println(touchX);
      
      Serial.print("Data y");
      Serial.println(touchY);

    }

    return false; /*Return `false` because we are not buffering and no more data to read*/
}

lv_obj_t * gauge1;
long date = 0;
uint8_t date_cotter = 0;

void setup() {

  //屏幕背光采用PWM调光
  ledcSetup(10, 5000/*freq*/, 10 /*resolution*/);
  ledcAttachPin(TFT_BL, 10);
  analogReadResolution(10);
  ledcWrite(10,1023);

  Serial.begin(115200); /* prepare for possible serial debug */

  lv_init();

  #if USE_LV_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
  #endif
  
  //屏幕初始化
  tft.begin(); /* TFT init */
  tft.setRotation(1);

  //触摸初始化
  touch.setCal(481, 3395, 755, 3487, 480, 320, 1);
  //旋转
  touch.setRotation(3);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  //显示刷新接口
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  //触摸板输入接口
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);             /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER;    /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;      /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);         /*Finally register the driver*/

   //放置仪表盘控件
    static lv_color_t needle_colors[1];
    needle_colors[0] = LV_COLOR_PURPLE;
    //gauge控件
    gauge1 = lv_gauge_create(lv_scr_act(), NULL);
    lv_gauge_set_needle_count(gauge1, 1, needle_colors);
    lv_obj_set_size(gauge1, 300, 300);
    lv_obj_align(gauge1, NULL, LV_ALIGN_CENTER, 0, 0);
    //设置仪表指针指向的值
    lv_gauge_set_value(gauge1, 0, 0);

    date = millis();
}

void loop() {
  lv_task_handler(); /* let the GUI do its work */
  delay(5);
  if(millis()-date>20)
  {
    date = millis();
    date_cotter++;
    date_cotter = date_cotter>100?0:date_cotter;
    //刷新仪表指针指向的值
    lv_gauge_set_value(gauge1, 0, date_cotter);
    Serial.printf("date_cotter: %d\n",date_cotter);
  }
}
