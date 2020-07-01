#include <BluetoothSerial.h>     //呼叫ESP32藍芽lib
BluetoothSerial SerialBT;        //宣告藍芽物件=SerialBT
int val;
String LED_num,Light_num,Choose_light,F;
int led_num,light_num,choose_light,f,f1;
float HZ=100.00;
/*
 * LED_num        幾顆LED同時動作
 * Light_num      LED亮度
 * choose_light   1-->呼吸燈  0-->一般燈
 */
int pin[10] = {25,26,27,19,12,13,4,16,17,21};
#include <EEPROM.h>

int i = 0,j=0;
void setup() {
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);digitalWrite(pin[i],LOW);}
  SerialBT.begin("TTRI_Breath_light");//<<藍芽名稱，請自己記得   
  Serial.begin(115200);
  EEPROM.begin(7); 
  delay(1000);
}
void loop() {
  if(SerialBT.available() ) {
    val=SerialBT.read();
    //利用ASCII碼讀取數值
    if(val==44){//ACSII44=,
      j++;
      if(i<3){i++;}
      else{i=0;}
      if(j%4==0){
        //記錄到FLASH裡面  toInt為強制轉成數字型態
        EEPROM.write(0, LED_num.toInt()); 
        EEPROM.write(1, Light_num.toInt()/4);
        EEPROM.write(2, Light_num.toInt()/4);
        EEPROM.write(3, Light_num.toInt()/4);
        EEPROM.write(4, Light_num.toInt()/4);
        EEPROM.write(5, Choose_light.toInt()); 
        EEPROM.write(6, F.toInt()); 
        EEPROM.commit();
        LED_num="";Light_num="";Choose_light="";F="";
      }
    }else{
      if(i==0){LED_num+=String(val-48);}//ASCII48=0
      else if(i==1){Light_num+=String(val-48);}
      else if(i==2){Choose_light+=String(val-48);}
      else if(i==3){F+=String(val-48);}
    }
  }
  eeprom();
  if(choose_light==0){pwmLed();}
  else if (choose_light==1){breathing();}
  else if (choose_light==2){forward();}
  else if (choose_light==3){back();}
  else if (choose_light==4){random_led();}
}
void eeprom(){

  led_num=EEPROM.read(0); 
  light_num=(EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4))*(1000000/HZ/1000);
  choose_light=EEPROM.read(5);
  f=EEPROM.read(6)*100;//換算成ms
  f1=light_num*0.8/(EEPROM.read(6)*100);//把0-20轉換為0-800
  
  }

void breathing(){
   for(int a =0;a<light_num*0.8;a+=f1){
    if(SerialBT.available() ) {break;}//當有接收到藍芽就重製
    for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], HIGH);}
    delayMicroseconds(a); 
    for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], LOW);}
    delayMicroseconds((1000000/HZ) - a);
  }
  for(int a =light_num*0.8;a>0;a-=f1){
    if(SerialBT.available() ) {break;}//當有接收到藍芽就重製
    for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], HIGH);}
    delayMicroseconds(a);
    for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], LOW);}
    delayMicroseconds((1000000/HZ) - a);
  } 
}

void pwmLed(){

  for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], HIGH);}
  delayMicroseconds(light_num); 
  for(int i = 0 ; i < led_num ; i++){digitalWrite(pin[i], LOW);}
  delayMicroseconds((1000000/HZ) - light_num); 
}

void forward(){
  for(int i = 0 ; i < 10 ; i++){
    if(SerialBT.available() ) {break;}//當有接收到藍芽就重製
    digitalWrite(pin[i], HIGH);
    delay(f);
    digitalWrite(pin[i], LOW);

  }
}

void back(){
  for(int i = 9 ; i > -1 ; i--){
    if(SerialBT.available() ) {break;}
    digitalWrite(pin[i], HIGH);
    delay(f);
    digitalWrite(pin[i], LOW);

  }
}

void random_led(){
  int i,j,n[10];
  //亂數10次不重複
  for (i = 0 ; i < 10 ; i++){
    if(SerialBT.available() ) {break;}//當有接收到藍芽就重製
    do{
      n[i-1]=random(0, 10);
      for(j = 0 ; j < i ; j++){
        if(SerialBT.available() ) {break;}//當有接收到藍芽就重製
        if(n[i-1]==n[j-1]){break;}
      }
    }while(j!=i);
  digitalWrite(pin[n[i-1]], HIGH);
  delay(f); 
  digitalWrite(pin[n[i-1]], LOW);    
  }
  

}
