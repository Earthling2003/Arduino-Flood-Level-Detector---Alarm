#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int echoPin = 7;
int trigPin = 6;
int lowLevel = 5;
int midLevel = 10;
int highLevel = 15;

//LED LIGHTS
int green = 8;
int yellow = 4;
int red = 13;

//Buzzer
int BuzzPin = 5;
int BuzzSounds[] = {200, 500, 700};
int BuzzDuration[] = {1, 3, 8};

float duration, inches;

void setup() {
  //setting up
  Serial.begin(9600);
  //lcd
  lcd.init();
  lcd.backlight();
  lcd.print("Flood Alarm");
  delay(2000);
  lcd.clear();
  //Buzzer
  pinMode(BuzzPin, OUTPUT);
  digitalWrite(BuzzPin, LOW);
  
  //LED LIGHTS
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

  digitalWrite(green, HIGH);
  digitalWrite(yellow, HIGH);
  digitalWrite(red, HIGH);
  delay(100);
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  
  //ultrasonic sensor
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  inches = ((duration/2)*0.0133);
  lcd.setCursor(0,0);
  lcd.print("Distance:");
  lcd.setCursor(0,1);
  lcd.print(inches);
  lcd.print("inches");
  delay(10);
 
  if (inches <= lowLevel && inches >= 0){
    digitalWrite(green, HIGH);
    delay(1000);
    tone(BuzzPin, 400, 500);
    noTone(BuzzPin);
    digitalWrite(green, LOW);
  }

  else if (inches <= highLevel && inches > lowLevel){
    digitalWrite(yellow, HIGH);
    delay(1000);
    tone(BuzzPin, 400, 500);
    noTone(BuzzPin);
    digitalWrite(yellow, LOW);
  }
 else if (inches > highLevel){
    digitalWrite(red, HIGH);
    delay(1000);
    tone(BuzzPin, 400, 500);
    noTone(BuzzPin);
    digitalWrite(red, LOW);
  }


}
