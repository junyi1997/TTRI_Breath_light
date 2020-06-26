long randNumber;

String LED_num,Light_num,Choose_light,F;
int led_num,light_num,choose_light,f,f1;
float HZ=100.00;
int pin[10] = {25,26,27,19,12,13,4,16,17,21};
void setup() {
  Serial.begin(115200);

  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  //randomSeed(analogRead(0));
  // print a random number from 10 to 19
  randNumber = random(1, 10);
  Serial.println("");
  Serial.print("randNumber：");
  Serial.println(randNumber);
  int i,j,n[10];
  for (i = 0 ; i < randNumber ; i++){
    do{
      n[i-1]=random(0, 10);
      for(j = 0 ; j < i ; j++){
        if(n[i-1]==n[j-1]){break;}
      }
    }while(j!=i); 
    
  }
  Serial.println("START");
  for (int ii = 0 ; ii < randNumber ; ii++){Serial.println(n[ii-1]);}
  
  /*
  
  for(int i = 0 ; i < 10;i++){pinMode(pin[i], OUTPUT);digitalWrite(pin[i],LOW);}
  for(int ii = 0 ; ii < randNumber ; ii++){digitalWrite(pin[i], HIGH);}
  delayMicroseconds(light_num);
  for(int ii = 0 ; ii < randNumber ; ii++){digitalWrite(pin[i], LOW);}
  delayMicroseconds((1000000/HZ) - light_num); 

  */ 
   
  Serial.println("END");
}

void loop() {

}
