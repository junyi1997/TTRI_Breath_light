/* 該代碼從EEPROM讀取4096字節數據 */

#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 
  Serial.println(""); 
  Serial.println("Start read");
  EEPROM.begin(4096); //申請操作到地址4095（比如你只需要讀寫地址為100上的一個字節，該處也需輸入參數101）
  
  for(int addr = 0; addr<4096; addr++) {
    int data = EEPROM.read(addr); //讀數據
    
    Serial.print(data); 
    Serial.print(" "); 
    delay(2);
    if((addr+1)%256 == 0){ //每讀取256字節數據換行 
      Serial.println(""); 
    } 
  }
  Serial.println("End read"); 
}

void loop() {
  // put your main code here, to run repeatedly:
}
