#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
String statusDoor;
int led = 8;
int button = 7;

void setup(){
  lcd.begin(16, 2); 
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop(){
  if(digitalRead(button)== HIGH){ 
  statusDoor = "door closed";
  digitalWrite(led, LOW);  
  }
  else{ 
  statusDoor = "door open";
  digitalWrite(led, HIGH); 
  } 
  
  lcd.setCursor(0, 1);
  lcd.print(statusDoor);
}
