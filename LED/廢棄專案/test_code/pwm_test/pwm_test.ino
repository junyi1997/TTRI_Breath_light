
int pin[6] = {25,26,27,14,12,13};
int VRpin = 39;
void setup() {
  Serial.begin(115200);
  for(int i = 0 ; i < 6;i++){pinMode(pin[i], OUTPUT);}
  pinMode(VRpin, INPUT);
}
void loop(){
  int a= map(analogRead(VRpin), 0, 4095, 0, 1000);
  Serial.println(a);
  for(int i = 0 ; i < 6;i++){
    digitalWrite(pin[i], HIGH);
    delayMicroseconds(a); // Approximately 10% duty cycle @ 1KHz
    digitalWrite(pin[i], LOW);
    delayMicroseconds(1000 - a);
    delayMicroseconds(1000);
  }
  
}
