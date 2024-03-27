#include <Arduino.h>
#include <ESP32Servo.h>
Servo myservo;
int servoPin = 13;

int pos = 90; // 定義舵機轉動位置
void turn_mid_light()
{
  myservo.write(90);
}

void turn_light()
{
  myservo.write(90 + 90);
  delay(200);
  turn_mid_light();
}
void turn_off_light()
{
  myservo.write(90 - 90);
  delay(200);
  turn_mid_light();
}

void setup()
{
  myservo.attach(servoPin, 500, 2500); // 設置舵機控制腳位，並設置最小與最大脈寬
  Serial.begin(115200);                // 設置序列埠鮑率
  int init_angle = myservo.read();     // 讀取舵機初始角度
  if (init_angle != pos)
  {
    myservo.write(pos);
    delay(2000);
  };
}

void loop()
{
  turn_light();
  delay(500);
  turn_off_light();
  delay(500);
}
