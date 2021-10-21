#include <LiquidCrystal.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>

int a, distance;
//LiquidCrystal lcd(RS, E, D4, D5, D6, D7);
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);

//Bluetooth module
SoftwareSerial BTserial(0, 1); //RX | TX

//defining contrast, alternative of potentiometer
int Contrast = 5;

Servo servo;
int state;
int trig = 12;
int echo = 13;

void setup()
{
  state = 0; //closed

  Serial.begin(9600);
  BTserial.begin(9600);

  //Servo Motor
  servo.attach(4);
  servo.write(0);

  //Ultrasonic Sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  //IR Sensor
  pinMode(2, OUTPUT);
  pinMode(3, INPUT);

  //LCD
  analogWrite(11, Contrast); // proxy of potentiometer.
  lcd.begin(16, 2);
}

void loop()
{
  //sending-receiving data from ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  a = pulseIn(echo, HIGH);
  distance = a * 0.0343 / 2;
  //Serial.println(distance); // print value in serial monitor

  while (true)
  {
    if (distance <= 30 && state == 0 && distance != 0)
    {
      state = 1; //open
      servo.write(90);
      lcd.setCursor(0, 0);
      lcd.print("PLEASE SANITIZE");

      lcd.setCursor(2, 1);
      lcd.print("YOUR HANDS");
      delay(2000);
    }
    else if (state == 1 && distance > 30)
    {
      delay(1000);
      servo.write(0);
      state = 0;
      lcd.clear();
    }
  }

  //IR Sensor
  if (digitalRead(3) == LOW)
  {
    digitalWrite(2,HIGH);
    Serial.println("Dustbin full");
    // BTserial.print("Bin is almost full! ");
  }
  else
  {
    digitalWrite(2,LOW);
    Serial.println(" ");
  }
  delay(10);
}

