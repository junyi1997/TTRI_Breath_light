//http://IP位置/cmd?LED_Num=1&Light_Num=2&Breathe_Speed=2&Choose_Light=2
//http://192.168.100.8/cmd?LED_Num=10&Light_Num=540&Breathe_Speed=15&Choose_Light=0
#include <WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <WebServer.h>  // 提供網站伺服器功能的程式庫
///////////////////////////
#define SSID   "IFTTT"
#define PASSWORD  ""
///////////////////////////
WebServer server(80);   // 宣告網站伺服器物件與埠號

String LED_num,Light_num,Choose_light;
int led_num,light_num,choose_light;
/*
 * LED_num        幾顆LED同時動作
 * Light_num      LED亮度
 * Breathe_speed  呼吸速度
 * choose_light   1-->呼吸燈  0-->一般燈
 */
int pin[10] = {25,26,27,14,12,13,5,17,16,4};

#include <EEPROM.h>

// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send(200, "text/html",  
  " LED_Num = <b>" + LED_num + "</b><br>"+
  " Light_Num = <b>" + Light_num + "</b><br>"+
  " Choose_Light = <b>" + Choose_light + "</b><br>");
}

void setup() {

  Serial.begin(115200);
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);}

  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {delay(1);}

   Serial.println(WiFi.localIP());
    Serial.println("-----------------------------------------------------");
    server.on("/index.html", rootRouter); //處理首頁連結請求的事件
    server.on("/", rootRouter);
    server.on("/cmd", []() {
  ////////////////////////////////(若要加入更多筆資料，請由此下手)      
    
      LED_num=server.arg("LED_Num");
      Light_num=server.arg("Light_Num");
      Choose_light=server.arg("Choose_Light");
      EEPROM.write(0, LED_num.toInt()); 
      EEPROM.write(1, Light_num.toInt()/4);
      EEPROM.write(2, Light_num.toInt()/4);
      EEPROM.write(3, Light_num.toInt()/4);
      EEPROM.write(4, Light_num.toInt()/4);
      EEPROM.write(5, Choose_light.toInt()); 
      EEPROM.commit(); 
      
  ////////////////////////////////(若要加入更多筆資料，請由此下手)
      Serial.flush();
      server.send(200, "text/html", "OK" );
    }); 
    server.onNotFound([](){   // 處理「找不到指定路徑」的事件
      server.send(404, "text/plain", "File NOT found!");
    });
    server.begin();
    EEPROM.begin(7); 
}

void loop() {
  server.handleClient();  // 處理用戶連線
  eeprom();

  if(Choose_light=="1"){pwmLed();}
  else{breathing();}
  
}
void eeprom(){

  led_num=EEPROM.read(0); 
  light_num=(EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4));
  choose_light=EEPROM.read(5);
  
  /*Serial.print("LED_num：");
  //Serial.println(LED_num.toInt());
  Serial.println(led_num);
  
  Serial.print("Light_num：");
  //Serial.println(Light_num.toInt());
  Serial.println(light_num);
  
  Serial.print("Breathe_speed：");
  //Serial.println(Breathe_speed.toInt());
  Serial.println(breathe_speed);
  
  Serial.print("Choose_light：");
  //Serial.println(Choose_light.toInt());
  Serial.println(choose_light);*/
  }


void breathing(){
   for(int a =0;a<light_num;a++){
    server.handleClient();  // 處理用戶連線
    for(int i = 0 ; i < led_num;i++){
      digitalWrite(pin[i], HIGH);
      delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(pin[i], LOW);
      delayMicroseconds(1000 - a);
    }
  }
  for(int a =light_num;a>0;a--){
    server.handleClient();  // 處理用戶連線
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
    //delayMicroseconds(1000);
    /*digitalWrite(pin[i], HIGH);
    delayMicroseconds(light_num); // Approximately 10% duty cycle @ 1KHz
    digitalWrite(pin[i], LOW);
    delayMicroseconds(1000 - light_num);
    //delayMicroseconds(1000);*/
  }
}
