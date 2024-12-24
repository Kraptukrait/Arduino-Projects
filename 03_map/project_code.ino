int sensor = A0; // Define the analog pin A0 for the sensor
int ledRed = 8; // Define pin 8 for the red LED
int ledYellow = 9; // Define pin 9 for the yellow LED
int ledGreen = 10; // Define pin 10 for the green LED

void setup() {
  pinMode(sensor, INPUT); // Set the sensor pin as input
  pinMode(ledRed, OUTPUT); // Set the red LED pin as output
  pinMode(ledYellow, OUTPUT); // Set the yellow LED pin as output
  pinMode(ledGreen, OUTPUT); // Set the green LED pin as output
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  int value = analogRead(sensor); // Read the analog value from the sensor
  value = map(value, 0, 1023, 0, 255); // Map the value from 0-1023 to 0-255
  Serial.println(value); // Print the mapped value to the serial monitor

  // Light up the green LED for values 0-85
  if (value <= 85) {
    digitalWrite(ledGreen, HIGH); // Turn on the green LED
    digitalWrite(ledYellow, LOW); // Turn off the yellow LED
    digitalWrite(ledRed, LOW); // Turn off the red LED
  } 
  // Light up the yellow LED for values 86-170
  else if (value <= 170) {
    digitalWrite(ledGreen, LOW); // Turn off the green LED
    digitalWrite(ledYellow, HIGH); // Turn on the yellow LED
    digitalWrite(ledRed, LOW); // Turn off the red LED
  } 
  // Light up the red LED for values 171-255
  else if (value <= 255) {
    digitalWrite(ledGreen, LOW); // Turn off the green LED
    digitalWrite(ledYellow, LOW); // Turn off the yellow LED
    digitalWrite(ledRed, HIGH); // Turn on the red LED
  } 
  // If the value falls outside the expected range, turn off all LEDs
  else {
    digitalWrite(ledGreen, LOW); // Turn off the green LED
    digitalWrite(ledYellow, LOW); // Turn off the yellow LED
    digitalWrite(ledRed, LOW); // Turn off the red LED
  }
}
