unsigned int counterStart = 49911; // For ~1 second with prescaler 256

volatile int zaehler = 1;          // counter/state machine
volatile int sekundenZaehler = 0;  // second counter


void setup() {
  Serial.begin(9600);
  DDRD = 0b10000000; // pinMode for the LED (PD7 as output)

  TCCR1A = 0;
  TCCR1B = 0b00000101; // 16000000 / 256 = 62500 Hz => start value (see above)
  TIMSK1 = 0b00000001; // enable Timer1 overflow interrupt
  TCNT1 = counterStart; // preload counter for 1-second timing
}

ISR(TIMER1_OVF_vect) {
  sekundenZaehler += 1;

  switch (zaehler) {
    case 1:
      PORTD |= 0b10000000; // LED ON
      if (sekundenZaehler >= 1) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 2:
      PORTD &= ~0b10000000; // LED OFF
      if (sekundenZaehler >= 1) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 3:
      PORTD |= 0b10000000; // LED ON
      if (sekundenZaehler >= 2) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 4:
      PORTD &= ~0b10000000; // LED OFF
      if (sekundenZaehler >= 1) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 5:
      PORTD |= 0b10000000; // LED ON
      if (sekundenZaehler >= 3) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 6:
      PORTD &= ~0b10000000; // LED OFF
      if (sekundenZaehler >= 1) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 7:
      PORTD |= 0b10000000; // LED ON
      if (sekundenZaehler >= 4) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 8:
      PORTD &= ~0b10000000; // LED OFF
      if (sekundenZaehler >= 1) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 9:
      PORTD |= 0b10000000; // LED ON
      if (sekundenZaehler >= 5) {
        zaehler++;
        sekundenZaehler = 0;
      }
      break;

    case 10:
      PORTD &= ~0b10000000; // LED OFF
      if (sekundenZaehler >= 1) {
        zaehler = 1; // restart sequence
        sekundenZaehler = 0;
      }
      break;
  }

  TCNT1 = counterStart; // reset timer for next cycle
}

void loop() {
  // Nothing here — all logic handled by timer interrupt
}
