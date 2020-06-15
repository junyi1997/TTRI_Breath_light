// the number of the LED pin
//const int ledPin = 25;  // 16 corresponds to GPIO16
const int ledPin = 25;
const int ledPin1 = 26;
const int ledPin2 = 27;
const int ledPin3 = 14;
const int ledPin4 = 12;
const int ledPin5 = 13;
int LedPin[6]={25,26,27,14,12,13};
int VRpin = 39;
// setting PWM properties
const int freq = 1000;
const int ledChannel = 0;
const int resolution = 8;
 
void setup(){
  //宣告ledChannel特性
  ledcSetup(ledChannel, freq, resolution);
  
  //將上述ledChannel附加到ledPin腳位上
  
  /*ledcAttachPin(ledPin, ledChannel);
  ledcAttachPin(ledPin1, ledChannel);
  ledcAttachPin(ledPin2, ledChannel);
  ledcAttachPin(ledPin3, ledChannel);
  ledcAttachPin(ledPin4, ledChannel);
  ledcAttachPin(ledPin5, ledChannel);
  pinMode(VRpin, INPUT);*/
}
/* 
void loop(){
  Serial.println(map(analogRead(VRpin), 0, 4095, 0, 30));
  // 逐漸增加亮度
  for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle);
    Serial.println(map(analogRead(VRpin), 0, 4095, 0, 30));
    delay(5);
  }

  // 逐漸減低亮度
  for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
    // changing the LED brightness with PWM
    ledcWrite(ledChannel, dutyCycle); 
    Serial.println(map(analogRead(VRpin), 0, 4095, 0, 30));
    delay(5);
  }
}
*/
void loop(){
  for(int i = 0 ; i < 6 ; i++){ledcAttachPin(LedPin[i], ledChannel);}
  ledcWrite(ledChannel,128-128*cos(2*PI*(millis()%2001)/2000));
}
