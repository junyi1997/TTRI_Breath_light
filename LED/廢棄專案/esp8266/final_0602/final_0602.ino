//http://IP位置/cmd?A=1&B=2

#include <ESP8266WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <ESP8266WebServer.h>  // 提供網站伺服器功能的程式庫
///////////////////////////
#define SSID   "IFTTT"
#define PASSWORD  ""
///////////////////////////
ESP8266WebServer server(80);   // 宣告網站伺服器物件與埠號
int pin[10] = {1,2,3,4,5,6,7,8,12,0};
String LED_num,Light_num,Choose_light;
int led_num,light_num,choose_light;
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

WiFi.mode(WIFI_STA);
WiFi.begin(SSID, PASSWORD);
while (WiFi.status() != WL_CONNECTED) {delay(500);}
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
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);}
  EEPROM.begin(6);
}

void loop() {

  server.handleClient();  // 處理用戶連線
  eeprom();

  if(Choose_light=="1"){pwmLed();}
  else{breathing();}
}

void eeprom(){

  led_num=EEPROM.read(0); 
  light_num=EEPROM.read(1)+EEPROM.read(2)+EEPROM.read(3)+EEPROM.read(4);
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
  }
}
