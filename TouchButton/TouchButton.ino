// set pin numbers
const int touchPin = 4; // 使用 T0 获取数据
const int ledPin = 2; //板载led灯

// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

void setup(){
  Serial.begin(115200);
  delay(1000); // give me time to bring up serial monitor
  // initialize the LED pin as an output:
  pinMode (ledPin, OUTPUT);
}


void loop(){
  clickLoopFunc();
  }


void clickLoopFunc(){
  // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println("有触控，灯亮");
    return true;
  }
  else{
    // turn LED off
    // digitalWrite(ledPin, LOW);
    // Serial.println(" - LED off");
    return false;
  }
  delay(100);
}
