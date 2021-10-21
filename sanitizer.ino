int a, distance;
int relayPin = 7;
int trig = 12;
int echo = 13;
int water = A5;
int led = 5;
int run_pump_led = 3;
int water_level;


void setup() {
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(run_pump_led, OUTPUT);


  //Ultrasonic Sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(relayPin, HIGH);

  digitalWrite(led, LOW);
  digitalWrite(run_pump_led, LOW);

  

}

void loop() {

 // sending-receiving data from ultrasonic
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  a = pulseIn(echo, HIGH);
  distance = a * 0.0343 / 2;
  Serial.println(distance);
  
  water_level = analogRead(water);
//  Serial.print("Water level is: ");
//  Serial.println(a);

  if (distance <= 5 && distance != 0)
    {
      digitalWrite(relayPin, LOW);
      digitalWrite(run_pump_led,HIGH);
    }
    else
    {
     digitalWrite(relayPin, HIGH);
     digitalWrite(run_pump_led,LOW);
    }
    delay(10);

 if (water_level <= 10)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
     digitalWrite(led, LOW);
    }
  

}
