#define BLYNK_PRINT Serial//redefine  BLYNK_PRINT as Serial
#include <ESP8266WiFi.h>//header file for controlling wifi
#include <BlynkSimpleEsp8266.h>//header for blynk

char auth[] = "";// indentification of your board like phone number
char ssid[] = "";// your Hotspot name
char pass[] = "";// your Hotspot password


//......................motor................................
#define SC1 D0 // ena1 pin of motor driver/speed control of motor 1
#define SC2 D1 // ena2 pin of motor driver/speed control of motor 2
#define M1 D5 // motor1 wire 1
#define M2 D6 // motor1 wire 2
#define M3 D7 // motor2 wire 1
#define M4 D8 // motor2 wire 2

int spd=1000;


int F=0;
int B=0;
int L=0;
int R=0;
//....................forward()....................
void forward()
{
  analogWrite(SC1, spd); // writing the speed to left motor
  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor forward direction
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  //right motor forward direction
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("FORWARD");
}
//....................backward()....................
void backward()
{
  analogWrite(SC1, spd); // writing the speed to left motor
  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor backward direction
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  //right motor backward direction
  digitalWrite(M3, LOW);
  digitalWrite(M4, HIGH);
  delay(50);
  Serial.println("BACKWARD");
}
//....................left()....................
void left()
{
  analogWrite(SC1, spd); // writing the speed to left motor
  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor backward direction
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  //right motor forward direction
  digitalWrite(M3, HIGH);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("LEFT");
}
//....................right()....................
void right()
{
  analogWrite(SC1, spd); // writing the speed to left motor
  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor forward direction
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  //right motor backward direction
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("RIGHT");
}
//....................STOP()....................
void STOP()
{
 
  analogWrite(SC1, spd); // writing the speed to left motor
  analogWrite(SC2, spd); // writing the speed to right motor
  // left motor stop
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  //right motor stop
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
  delay(50);
  Serial.println("STOP");
}

//....................setup()....................
void setup() {
  pinMode(SC1,OUTPUT);
  pinMode(SC2,OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  // initially stop the motor
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
  digitalWrite(M4, LOW);
 
  Serial.begin(9600);//setting the speed of communication between your laptop and board

  Blynk.begin(auth, ssid, pass);// connecting to Network
}

//............................voice data.................

BLYNK_WRITE(V0)
{
  F = param.asInt(); // assigning incoming value from pin V1 to a f

}
BLYNK_WRITE(V1)
{
  B = param.asInt(); // assigning incoming value from pin V1 to a b

}
BLYNK_WRITE(V2)
{
  L = param.asInt(); // assigning incoming value from pin V1 to a l

}
BLYNK_WRITE(V3)
{
  R = param.asInt(); // assigning incoming value from pin V1 to a r
 
}



//....................loop()....................

void loop() {
  
 Blynk.run();//communicate to mobile
  if(F==1&&B==0&&R==0&&L==0)
  {
    forward();
    delay(5000);
    F=0;
  }
  else if(F==0&&B==1&&R==0&&L==0)
  {
    backward();
    delay(5000);
    B=0;
  }
  else if(F==0&&B==0&&R==0&&L==1)
  {
    left();
    delay(500);
    L=0;
  }
  else if(F==0&&B==0&&R==1&&L==0)
  {
    right();
    delay(500);
    R=0;
  }
  else
  {
    F=0;B=0;L=0;R=0;
    STOP();
  }
  
}
