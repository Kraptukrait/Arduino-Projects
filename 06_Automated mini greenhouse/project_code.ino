#include <Wire.h>
#include <DS3231.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#include <Servo.h>
#include <U8x8lib.h>
#include <Stepper.h>
#include "IRremote.h"
#include "IR.h"
#include <EEPROM.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

DS3231 clock;
RTCDateTime dt;
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
int redLED = 3;
Servo myservo;
const int stepsPerRevolution = 2048;
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);
bool stepperMotorActive = false;
int potentiometer = A0;
int whiteLED = 5;
int button = 6;
bool buttonClicked = false;
IRrecv irrecv(RECEIVER);
decode_results results;
bool start = false;
int counter = 0;
float eepromValue;

void setup() {
  myStepper.setSpeed(15);
  Serial.begin(9600);
  Serial.println("Initialize DS3231");
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
  u8x8.begin();
  u8x8.setPowerSave(0);
  pinMode(redLED, OUTPUT);
  myservo.attach(4);
  pinMode(potentiometer, INPUT);
  pinMode(whiteLED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  irrecv.enableIRIn();

  EEPROM.get(0, counter);
  Serial.print("Stored values: ");
  Serial.println(counter);

  for (int i = 0; i < counter; i++) {
    int addr = 2 + i * sizeof(float);
    EEPROM.get(addr, eepromValue);
    Serial.print("Value ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(eepromValue);
  }
}

static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();
  if (millis() - measurement_timestamp > 3000ul) {
    if (dht_sensor.measure(temperature, humidity) == true) {
      measurement_timestamp = millis();
      return true;
    }
  }
  return false;
}

void remoteControl() {
  if (irrecv.decode(&results)) {
    switch (results.value) {
      case 0xFFA25D:
        Serial.println("POWER");
        start = true;
        break;
      case 0xFFE21D: Serial.println("FUNC/STOP"); break;
      case 0xFF629D: Serial.println("VOL+"); break;
      case 0xFF22DD: Serial.println("FAST BACK"); break;
      case 0xFF02FD: Serial.println("PAUSE"); break;
      case 0xFFC23D: Serial.println("FAST FORWARD"); break;
      case 0xFFE01F: Serial.println("DOWN"); break;
      case 0xFFA857: Serial.println("VOL-"); break;
      case 0xFF906F: Serial.println("UP"); break;
      case 0xFF9867: Serial.println("EQ"); break;
      case 0xFFB04F: Serial.println("ST/REPT"); break;
      case 0xFF6897: Serial.println("0"); break;
      case 0xFF30CF: Serial.println("1"); break;
      case 0xFF18E7: Serial.println("2"); break;
      case 0xFF7A85: Serial.println("3"); break;
      case 0xFF10EF: Serial.println("4"); break;
      case 0xFF38C7: Serial.println("5"); break;
      case 0xFF5AA5: Serial.println("6"); break;
      case 0xFF42BD: Serial.println("7"); break;
      case 0xFF4AB5: Serial.println("8"); break;
      case 0xFF52AD: Serial.println("9"); break;
    }
    irrecv.resume();
  }
}

void loop() {
  remoteControl();
  if (start == true) {
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    dt = clock.getDateTime();
    Serial.print("Raw data: ");
    Serial.print(dt.year);
    Serial.print("-");
    Serial.print(dt.month);
    Serial.print("-");
    Serial.print(dt.day);
    Serial.print(" ");
    Serial.print(dt.hour);
    Serial.print(":");
    Serial.print(dt.minute);
    Serial.print(":");
    Serial.print(dt.second);
    Serial.println("");

    u8x8.setCursor(0, 0);
    u8x8.print("Time: ");
    u8x8.setCursor(8, 0);
    u8x8.print(dt.hour);
    u8x8.print(":");
    u8x8.print(dt.minute);
    u8x8.print(":");
    u8x8.print(dt.second);

    float temperature;
    float humidity;

    if (measure_environment(&temperature, &humidity) == true) {
      Serial.print("T = ");
      Serial.print(temperature, 1);
      Serial.print(" deg. C, H = ");
      Serial.print(humidity, 1);
      Serial.println("%");

      u8x8.setCursor(0, 1);
      u8x8.print("Temp:");
      u8x8.print(temperature);
      u8x8.print("C");
      u8x8.setCursor(0, 2);
      u8x8.print("Humid:");
      u8x8.print(humidity);
      u8x8.print("%");

      if (counter < 255) {
        EEPROM.put(2 + counter * sizeof(float), temperature);
        counter++;
        EEPROM.put(0, counter);
      }
    }

    if (temperature >= 28) {
      digitalWrite(redLED, HIGH);
      myservo.write(180);
    } else {
      digitalWrite(redLED, LOW);
      myservo.write(0);
    }

    if (humidity <= 40 && stepperMotorActive == false) {
      myStepper.step(stepsPerRevolution);
      stepperMotorActive = true;
    } else if (stepperMotorActive == true && humidity > 40) {
      myStepper.step(-stepsPerRevolution);
    }

    int potValue = analogRead(potentiometer);
    int mappedValue = map(potValue, 0, 1023, 0, 100);
    u8x8.setCursor(0, 3);
    u8x8.print("LED = ");
    u8x8.print(mappedValue);
    analogWrite(whiteLED, mappedValue);

    if (digitalRead(button) == LOW && buttonClicked == false) {
      buttonClicked = true;
      u8x8.clear();
      u8x8.setCursor(5, 5);
      u8x8.print("Test");
      digitalWrite(redLED, HIGH);
      delay(1000);
      digitalWrite(redLED, LOW);
      u8x8.clear();
      buttonClicked = false;
    }
    delay(1000);
  }
}
