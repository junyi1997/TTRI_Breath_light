//http://IP位置/cmd?A=1&B=2&C=2&D=2

#include <WiFi.h>      // 提供Wi-Fi功能的程式庫
#include <WebServer.h>  // 提供網站伺服器功能的程式庫
///////////////////////////
#define SSID   "19-1H5F"
#define PASSWORD  "2268159779"
///////////////////////////
WebServer server(80);   // 宣告網站伺服器物件與埠號
unsigned long t1,t2;
String cmd1,cmd2;
String LED_num,Light_num,Breathe_speed,choose_light;
// 定義處理首頁請求的自訂函式
void rootRouter() {
  server.send(200, "text/html",  
  " A = <b>" + LED_num + "</b><br>"+
  " B = <b>" + Light_num + "</b><br>"+
  " C = <b>" + Breathe_speed + "</b><br>"+
  " D = <b>" + choose_light + "</b><br>");
}

void setup() {
Serial.begin(9600);  
WiFi.mode(WIFI_STA);
WiFi.begin(SSID, PASSWORD);
while (WiFi.status() != WL_CONNECTED) {delay(500);}
 Serial.println(WiFi.localIP());
  Serial.println("-----------------------------------------------------");
  server.on("/index.html", rootRouter); //處理首頁連結請求的事件
  server.on("/", rootRouter);
  server.on("/cmd", []() {
    /*
    cmd1="";
    cmd2="";
    cmd1=server.arg("A");
    cmd2=server.arg("B");
    */
    LED_num="";
    Light_num="";
    Breathe_speed="";
    choose_light="";
    
    LED_num=server.arg("A");
    Light_num=server.arg("B");
    Breathe_speed=server.arg("C");
    choose_light=server.arg("D");
////////////////////////////////(若要加入更多筆資料，請由此下手)
    /*
    Serial.print(cmd1);
    Serial.print(",");
    Serial.println(cmd2);
    */
    /*
    Serial.print("LED_num：");
    Serial.println(LED_num);
    Serial.print("Light_num：");
    Serial.println(Light_num);
    Serial.print("Breathe_speed：");
    Serial.println(Breathe_speed);
    Serial.print("choose_light：");
    Serial.println(choose_light);
    */
    Serial.println("已更新");
////////////////////////////////(若要加入更多筆資料，請由此下手)
    Serial.flush();
    server.send(200, "text/html", "OK" );
  }); 
  server.onNotFound([](){   // 處理「找不到指定路徑」的事件
    server.send(404, "text/plain", "File NOT found!");
  });
  server.begin();
}

void loop() {
  Serial.print("LED_num：");
  Serial.println(LED_num);
  Serial.print("Light_num：");
  Serial.println(Light_num);
  Serial.print("Breathe_speed：");
  Serial.println(Breathe_speed);
  Serial.print("choose_light：");
  Serial.println(choose_light);
  server.handleClient();  // 處理用戶連線
}
