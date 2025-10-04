int led1 = 9;
int led2 = 10;
int led4 = 11;
int led8 = 12;

int counter = 0;

bool button = false;


void setup()
{
  DDRB = 0b00011110;
  PORTB = 0b00000001;
  DDRD = 0b10000000;
  /*
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led8, OUTPUT);
  */
}

void loop()
{
  if((PINB & 0b00000001) == 0){
    button = true;
    PORTB &= ~(0b00011110);
    PORTD |= 0b10000000;
  }
  if(button == true){
  if(counter == 1 || counter == 3 || counter == 5 || counter == 7 || counter == 9 ){
  	PORTB |= (1<<1);
    //PORTB |= 0b00000010;
    //digitalWrite(led1, HIGH);
  }else{
  	PORTB &= ~(1<<1);
    //PORTB &= ~(0b00000010);
    //digitalWrite(led1, LOW);
  }
  
  if(counter == 2 || counter == 3 || counter == 6 || counter == 7 ){
  	PORTB |= (1<<2);
    //PORTB |= 0b00000100;
    //digitalWrite(led2, HIGH);
  }else{
  	PORTB &= ~(1<<2);
    //PORTB &= ~(0b00000100);
    //digitalWrite(led2, LOW);
  }
  
  if(counter == 4 || counter == 5 || counter == 6 || counter == 7 ){
  	PORTB |= (1<<3);
    //PORTB |= 0b00001000;
    //digitalWrite(led4, HIGH);
  }else{
    PORTB &= ~(1<<3);
  	//PORTB &= ~(0b00001000);
    //digitalWrite(led4, LOW);
  }
  
  if(counter == 8 || counter == 9 ){
  	PORTB |= (1<<4);
    //PORTB |= 0b00010000;
    //digitalWrite(led8, HIGH);
  }else{
    PORTB &= ~(1<<4);
  	//PORTB &= ~(0b00010000);
    //digitalWrite(led8, LOW);
  }
  if(counter == 10){
  	counter = 0;
  }
  
  counter += 1;
  delay(500);
  }else{
  PORTB |= 0b00011110;
  }
}
