#include <Arduino.h>

// 任务1
#define TASK1_TASK_PRIO  1          // 任务优先级
#define TASK1_STK_SIZE   1024        // 任务堆栈大小
TaskHandle_t Tasks1_TaskHandle; // 任务句柄
void task1(void *pvParameters); //任务函数

// 任务2
#define TASK2_TASK_PRIO  1        // 任务优先级
#define TASK2_STK_SIZE   1024        // 任务堆栈大小
TaskHandle_t Tasks2_TaskHandle; // 任务句柄
void task2(void *pvParameters); //任务函数

// 任务3
#define TASK3_TASK_PRIO  1          // 任务优先级
#define TASK3_STK_SIZE   1024        // 任务堆栈大小
TaskHandle_t Tasks3_TaskHandle; // 任务句柄
void task3(void *pvParameters); //任务函数

void setup()
{
    Serial.begin(115200);
    // 创建任务
  
    xTaskCreate(task1, "task1_task",TASK1_STK_SIZE,NULL,TASK1_TASK_PRIO,NULL); 

    xTaskCreate(task2, "task2_task",TASK2_STK_SIZE,NULL,TASK2_TASK_PRIO,NULL);

    xTaskCreate(task3, "task3_task",TASK3_STK_SIZE,NULL,TASK3_TASK_PRIO,NULL);
    vTaskStartScheduler(); //启动调度
}
void loop() 
{

}


void task1(void *pvParameters)
{
    while(true)
    {
        Serial.println("task1 runing........");
        vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
    }
}

void task2(void *pvParameters)
{
    while(true)
    {
        Serial.println("task2 runing........");
        vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
    }
    
}
void task3(void *pvParameters)
{
     while(true)
    {
        Serial.println("task3 runing........");
        vTaskDelay(100/portTICK_PERIOD_MS); //等待1s
    }
}
