#include <NTPClient.h>
#include <WiFi.h> // for WiFi shield
#include <WiFiUdp.h>
const char* ssid = "Xiaomi_2304";
const char* password = "15300786298";
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"ntp.aliyun.com");  //NTP服务器地址
void setup(){
  Serial.begin(115200);
  //连接wifi
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
    timeClient.begin();
    timeClient.setTimeOffset(28800);  // + 1区 偏移3600， +8区 ：3600×8 = 28800  
}
void loop() {
//  timeClient.update();
//  //打印时间
//  Serial.println(timeClient.getFormattedTime());
//  delay(1000);

timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    Serial.print("Epoch Time: ");
    Serial.println(epochTime);
    //打印时间
    int currentHour = timeClient.getHours();
    Serial.print("Hour: ");
    Serial.println(currentHour);
    int currentMinute = timeClient.getMinutes();
    Serial.print("Minutes: ");
    Serial.println(currentMinute);
    int weekDay = timeClient.getDay();
    Serial.print("Week Day: ");
    Serial.println(weekDay);
    //将epochTime换算成年月日
    struct tm *ptm = gmtime ((time_t *)&epochTime);
    int monthDay = ptm->tm_mday;
    Serial.print("Month day: ");
    Serial.println(monthDay);
    int currentMonth = ptm->tm_mon+1;
    Serial.print("Month: ");
    Serial.println(currentMonth);
    delay(1000);

}
