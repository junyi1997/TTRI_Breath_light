int pin[10] = {25,26,27,14,12,13,0,0,0,0};
int VRpin = 39;
int a=0;
void setup() {
  Serial.begin(115200);
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);}
  pinMode(VRpin, INPUT);
}

void loop(){
  int a=map(analogRead(VRpin), 0, 4095, 0, 1000);
  int b=map(analogRead(VRpin), 0, 4095, 0, 15);
  
  breathing(6,b);//breathing(幾顆LED上限10,延遲多久上限15);
  //pwmLed(6,a);//pwmLed(幾顆LED上限10,亮度上限1000);
}

void breathing (int pinnum,int delaynum){
  //map(2048*sin(millis()),-2048,2048,0,4096)
  for(int i = 0 ; i < pinnum;i++){
    
      digitalWrite(pin[i], 128-128*cos(2*PI*millis()));
      
  }
   /*for(int a =0;a<1000;a++){
    for(int i = 0 ; i < pinnum;i++){
      digitalWrite(pin[i], HIGH);
      delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(pin[i], LOW);
      delayMicroseconds(1000 - a);
    }
    delay(delaynum);
  }
  for(int a =1000;a>0;a--){
    for(int i = 0 ; i < pinnum;i++){
      digitalWrite(pin[i], HIGH);
      delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
      digitalWrite(pin[i], LOW);
      delayMicroseconds(1000 - a);
    }
    delay(delaynum);
  } */
  
}
void pwmLed(int pinnum , int light){
  for(int i = 0 ; i < pinnum ; i++){
    digitalWrite(pin[i], HIGH);
    delayMicroseconds(light); // Approximately 10% duty cycle @ 1KHz
    digitalWrite(pin[i], LOW);
    delayMicroseconds(1000 - light);
    //delayMicroseconds(1000);
  }
}
