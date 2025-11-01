int light1_red = 7;
int light1_yellow = 6;
int light1_green = 5;

int light2_red = 13;
int light2_yellow = 12;
int light2_green = 11;

int light2_wait = 10;

int button = 2;
int counter = 0;

volatile bool buttonPressed = false;

void setup()
{
  pinMode(light1_red, OUTPUT);
  pinMode(light1_yellow, OUTPUT);
  pinMode(light1_green, OUTPUT);
  
  pinMode(light2_red, OUTPUT);
  pinMode(light2_yellow, OUTPUT);
  pinMode(light2_green, OUTPUT);
  pinMode(light2_wait, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), isrToggleLed, FALLING);
  
  // LED test
  digitalWrite(light1_red, HIGH);
  digitalWrite(light1_yellow, HIGH);
  digitalWrite(light1_green, HIGH);
  
  digitalWrite(light2_red, HIGH);
  digitalWrite(light2_yellow, HIGH);
  digitalWrite(light2_green, HIGH);
  digitalWrite(light2_wait, HIGH);
  
  delay(1000);
  
  digitalWrite(light1_red, LOW);
  digitalWrite(light1_yellow, LOW);
  digitalWrite(light1_green, LOW);
  
  digitalWrite(light2_red, LOW);
  digitalWrite(light2_yellow, LOW);
  digitalWrite(light2_green, LOW);
  digitalWrite(light2_wait, LOW);
  // End of test
}

void loop()
{
  digitalWrite(light1_red, HIGH);
  digitalWrite(light2_red, HIGH);
  //delay(2000);
  digitalWrite(light1_red, HIGH);
  digitalWrite(light1_yellow, LOW);
  digitalWrite(light1_green, LOW);
  delay(5000);
  digitalWrite(light1_yellow, HIGH);
  digitalWrite(light1_green, LOW);
  delay(1000);
  digitalWrite(light1_red, LOW);
  digitalWrite(light1_yellow, LOW);
  digitalWrite(light1_green, HIGH);
  delay(5000);
  digitalWrite(light1_red, LOW);
  digitalWrite(light1_yellow, HIGH);
  digitalWrite(light1_green, LOW);
  delay(1000);
  digitalWrite(light1_red, HIGH);
  digitalWrite(light1_yellow, LOW);
  digitalWrite(light1_green, LOW);
  delay(3000);
  digitalWrite(light2_yellow, LOW);
  digitalWrite(light2_green, LOW);
  delay(1000);
  digitalWrite(light2_yellow, HIGH);
  digitalWrite(light2_green, LOW);
  delay(2000);
  digitalWrite(light2_red, LOW);
  digitalWrite(light2_yellow, LOW);
  digitalWrite(light2_green, HIGH);
  digitalWrite(light2_wait, LOW);
  delay(2000);
  if(buttonPressed == true){
    buttonPressed = false;
    digitalWrite(light2_wait, LOW);
    digitalWrite(light2_green, LOW);
    digitalWrite(light2_yellow, HIGH);
    delay(500);
    digitalWrite(light2_yellow, LOW);
    digitalWrite(light2_red, HIGH);
  }else{
    counter = 0;
    while(counter <= 100 && buttonPressed == false){
      delay(30);
      counter += 1;
    }
    digitalWrite(light2_wait, LOW);
  	digitalWrite(light2_red, LOW);
  	digitalWrite(light2_yellow, HIGH);
  	digitalWrite(light2_green, LOW);
    delay(1000);
  	digitalWrite(light2_red, HIGH);
  	digitalWrite(light2_yellow, LOW);
  	digitalWrite(light2_green, LOW);
  }
}

void isrToggleLed() { 
  buttonPressed = true;
  if(buttonPressed == true){
    digitalWrite(light2_wait, HIGH);
  }
}
