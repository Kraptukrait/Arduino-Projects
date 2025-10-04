bool button = false;
void setup()
{
  DDRB = 0b00000111;
  PORTB = 0b00001000;
}

void loop()
{
  if((PINB & 0b00001000) == 0){
    delay(50);
    if((PINB & 0b00001000) == 0){
    button = !button;
      }
    }
  if(button == false){
    PORTB |= 0b00000100;
    delay(1000);
    PORTB &= ~(0b00000100);
    delay(1000);
    PORTB |= 0b00000010;
    delay(1000);
    PORTB &= ~(0b00000010);
    delay(1000);
    PORTB |= 0b00000001;
    delay(1000);
    PORTB &= ~(0b00000001);
    delay(1000);
  }else{
    PORTB |= 0b00000001;
    delay(1000);
    PORTB &= ~(0b00000001);
    delay(1000);
    PORTB |= 0b00000010;
    delay(1000);
    PORTB &= ~(0b00000010);
    delay(1000);
    PORTB |= 0b00000100;
    delay(1000);
    PORTB &= ~(0b00000100);
    delay(1000);
  }
}
