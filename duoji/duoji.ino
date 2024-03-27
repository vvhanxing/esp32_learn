#include <Arduino.h>

int freq = 50;      // 1/50秒，50Hz的频率，20ms的周期，这个变量用来存储时钟基准。
int channel = 8;    // 通道(高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动。)
int resolution = 8; // 分辨率设置为8，就是2的8次方，用256的数值来映射角度，看下方的占空比函数。
const int led = 13;

int calculatePWM(int degree) //定义函数用于输出PWM的占空比
{ //0-180度
 //20ms周期内，高电平持续时长0.5-2.5ms，对应0-180度舵机角度，参考上面的180度对应图。
  const float deadZone = 6.4;//对应0.5ms（0.5ms/(20ms/256）)
  const float max = 32;//对应2.5ms（2.5ms/（20ms/256））
  if (degree < 0)
    degree = 0;
  if (degree > 180)
    degree = 180;
  return (int)(((max - deadZone) / 180) * degree + deadZone); //返回度数对应的高电平的数值
}

void setup()
{
  Serial.begin(9600);
  ledcSetup(channel, freq, resolution); // 用于设置 LEDC 通道的频率和分辨率。
  ledcAttachPin(led, channel);          // 将通道与对应的引脚连接
}

void loop()
{
  for (int d = 0; d <= 180; d += 10)
  {
    ledcWrite(channel, calculatePWM(d)); // 输出PWM，设置 LEDC 通道的占空比。
    Serial.printf("value=%d,calcu=%d\n", d, calculatePWM(d));
    delay(2000);
  }  
}
