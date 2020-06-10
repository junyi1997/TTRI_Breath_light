#include <EEPROM.h> 

int led_num=10,light_num=548,breathe_speed=15,choose_light=2;
int LED_num,Light_num,Breathe_speed,Choose_light;
void setup() { 
  Serial.begin(115200); 
  Serial.println(""); //////////第一次寫入 
  Serial.println("申請操作到地址9"); 
  Serial.println("向地址0~9分別寫入數據0~9然後提交"); 
  EEPROM.begin(7);
  for (int addr = 0; addr < 7; addr++) { EEPROM.write(addr, addr); } 
  EEPROM.commit();   
  EEPROM.begin(7); 
  EEPROM.write(0, led_num); 
  EEPROM.write(1, light_num/4);
  EEPROM.write(2, light_num/4);
  EEPROM.write(3, light_num/4);
  EEPROM.write(4, light_num/4);
  EEPROM.write(5, breathe_speed); 
  EEPROM.write(6, choose_light); 
  EEPROM.commit(); 
  EEPROM.begin(7);
  LED_num=EEPROM.read(0); 
  Light_num=EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4);
  Breathe_speed=EEPROM.read(5);
  Choose_light=EEPROM.read(6);
  
  Serial.print("LED_num：");
  Serial.println(LED_num);
  
  Serial.print("Light_num：");
  Serial.println(Light_num);
  
  Serial.print("Breathe_speed：");
  Serial.println(Breathe_speed);
  
  Serial.print("Choose_light：");
  Serial.println(Choose_light);
  /*for (int addr = 0; addr < 7; addr++) {
    int data = EEPROM.read(addr); 
    Serial.print(data); 
    Serial.print(" ");
  } */
  Serial.println(""); 
  Serial.println("");
} 
void loop() { }
