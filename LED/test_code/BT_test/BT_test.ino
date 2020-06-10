#include <BluetoothSerial.h>     //呼叫ESP32藍芽lib
BluetoothSerial SerialBT;        //宣告藍芽物件=SerialBT
int val;
String LED_num,Light_num,Choose_light;
int led_num,light_num,choose_light;
/*
 * LED_num        幾顆LED同時動作
 * Light_num      LED亮度
 * choose_light   1-->呼吸燈  0-->一般燈
 */
int pin[10] = {25,26,27,14,12,13,5,17,16,4};
#include <EEPROM.h>

int i = 0,j=0;
void setup() {
  SerialBT.begin("TTRI_Breath_light");//<<藍芽名稱，請自己記得   
  Serial.begin(115200);
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);}
  EEPROM.begin(7); 
}
void loop() {
  if(SerialBT.available() ) {
    val=SerialBT.read();
    if(val==44){
      j++;
      if(i<2){i++;}
      else{i=0;}
      if(j%3==0){
        Serial.print("LED_num ：");Serial.println(LED_num);
        Serial.print("Light_num ：");Serial.println(Light_num);
        Serial.print("Choose_light ：");Serial.println(Choose_light);
        EEPROM.write(0, LED_num.toInt()); 
        EEPROM.write(1, Light_num.toInt()/4);
        EEPROM.write(2, Light_num.toInt()/4);
        EEPROM.write(3, Light_num.toInt()/4);
        EEPROM.write(4, Light_num.toInt()/4);
        EEPROM.write(5, Choose_light.toInt()); 
        EEPROM.commit();
        LED_num="";Light_num="";Choose_light="";
      }
    }else{
      if(i==0){LED_num+=String(val-48);}
      else if(i==1){Light_num+=String(val-48);}
      else if(i==2){Choose_light+=String(val-48);}
    }
  }
  eeprom();
  if(choose_light==0){pwmLed();}
  else{breathing();}
}
void eeprom(){

  led_num=EEPROM.read(0); 
  light_num=(EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4));
  choose_light=EEPROM.read(5);
  
  Serial.print("LED_num：");
  //Serial.println(LED_num.toInt());
  Serial.println(led_num);
  
  Serial.print("Light_num：");
  //Serial.println(Light_num.toInt());
  Serial.println(light_num);
  
  Serial.print("Choose_light：");
  //Serial.println(Choose_light.toInt());
  Serial.println(choose_light);
  }


void breathing(){
   for(int a =0;a<light_num;a++){
    if(SerialBT.available() ) {break;}
    for(int i = 0 ; i < led_num;i++){
      digitalWrite(pin[i], HIGH);
      delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(pin[i], LOW);
      delayMicroseconds(1000 - a);
    }
  }
  for(int a =light_num;a>0;a--){
    if(SerialBT.available() ) {break;}
    for(int i = 0 ; i < led_num;i++){
      digitalWrite(pin[i], HIGH);
      delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(pin[i], LOW);
      delayMicroseconds(1000 - a);
    }
  } 
}

void pwmLed(){
  for(int i = 0 ; i < led_num ; i++){
    digitalWrite(pin[i], HIGH);
    delayMicroseconds(light_num); // Approximately 10% duty cycle @ 1KHz
    digitalWrite(pin[i], LOW);   
    delayMicroseconds(1000 - light_num);
  }
}
