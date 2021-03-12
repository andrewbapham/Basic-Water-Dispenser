#include <SR04.h>

int waterSensorPin = 1;
int solenoidPin = 4;
int buttonPin = 6;
int trigPin = 12;
int echoPin = 11;
SR04 sr04 = SR04(echoPin, trigPin);
long distance;

char printBuffer[128];
int outputState = HIGH;
int reading;
int currentState = LOW;
long time = 0;
long debounce = 200;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  pinMode(solenoidPin, OUTPUT);
  digitalWrite(solenoidPin, LOW); 
  Serial.begin(9600);
}

void loop() {
  reading = digitalRead(buttonPin);
  distance = sr04.Distance();
  Serial.print(distance);
  Serial.println("cm");
  Serial.println(reading);
  int waterLevel = analogRead(waterSensorPin);
  sprintf(printBuffer, "Water level is %d", waterLevel);
  Serial.println(printBuffer);
  // Turns on the system when detect button press and if system is off; sets state to on
   if (waterLevel > 140){
    currentState = LOW;
    digitalWrite(solenoidPin, LOW);
    Serial.println("closing");
  }
  if (reading == HIGH && millis() - time > debounce){
    currentState = HIGH;
    time = millis();
  }
  if (currentState == HIGH){
    //execute code here
    digitalWrite(solenoidPin, HIGH);
  }
  Serial.println(reading);
  delay(500);
}
