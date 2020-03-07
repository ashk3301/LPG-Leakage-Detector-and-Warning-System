#define MQ2pin (A0)
#include <Servo.h> 
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2); // RX, TX 
Servo servo;
float sensorValue;  //variable to store sensor value
int buzz=4;
int p = 9;
int c = 0;
String num="ATD 7007231250;";
//int buzz1=5;
int i = 1;
void setup()
{ 
  
  pinMode(buzz,OUTPUT);
  Serial.begin(9600); // sets the serial port to 9600
  
   delay(1000);
   mySerial.begin(9600);
   Serial.println("Testing SIM800L module");
  Serial.println("Gas sensor warming up!");
   Serial.println();
    Serial.print("Sizeof(mySerial) = "); Serial.println(sizeof(mySerial));
      Serial.println();
  servo.attach(p);
  delay(10000); // allow the MQ-6 to warm up
  

}
void rotate(){
  for(i=90; i>=1; i--){
    servo.write(i);
    delay(15);
  }
}
void call(){
   Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  Serial.println("AT");
  mySerial.println("ATD 7007231250;"); 
  updateSerial();
  delay(20000); // wait for 20 seconds...
  mySerial.println("ATH"); //hang up
 
  updateSerial();
 Serial.println("ATH");

}
void buzzer()
{
  digitalWrite(buzz,HIGH);
   //digitalWrite(buzz1,HIGH);
  delay(100);
  //digitalWrite(buzz1,LOW);
}
void loop()
{
  sensorValue = analogRead(MQ2pin); // read analog input pin 0
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  if(sensorValue > 400)
  { 
    Serial.print(" | Smoke detected!");
    buzzer();
    if(c==7){
      rotate();
      call();
      
    }
    c++;
  }
  else
  {
     digitalWrite(buzz,LOW);
  }
  
  Serial.println("");
  delay(1000); // wait 1s for next reading
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
