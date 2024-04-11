#include <Stepper.h>

// 定义步进电机参数
const int stepsPerRevolution =200;  // 步进电机一圈的步数
const int motorPin1 = 2;  // 步进电机控制引脚1
const int motorPin2 = 3;  // 步进电机控制引脚2
const int motorPin3 = 4;  // 步进电机控制引脚3
const int motorPin4 = 5;  // 步进电机控制引脚4

// 创建步进电机对象
Stepper myStepper(stepsPerRevolution, motorPin1, motorPin2, motorPin3, motorPin4);

void setup() {
  // 设置步进电机速度（每分钟转速）
  myStepper.setSpeed(120);
}

void loop() {
  // 旋转步进电机两圈
  myStepper.step(stepsPerRevolution * 16);
  //myStepper.step(120);
delay(1000);
}
