int led = 9;
int pot = A0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(pot, INPUT);
  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(pot);
  int mappedValue = map(potValue, 0, 1023, 0, 255);
  analogWrite(led, mappedValue);
  Serial.println(mappedValue);
}
