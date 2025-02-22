#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#include <Arduino.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <Wire.h>
#include <DS3231.h>

// Initialize DS3231 and RTC
DS3231 clock;
RTCDateTime dt;

// Define pins for the button and the red LED
int button = 8;
int ledRed = 7;
float maxTemperature = -100;

// Define the pin for the DHT sensor and initialize it
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);

// Initialize the OLED display
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/U8X8_PIN_NONE);

// Setup function runs once at startup
void setup() {
  // Initialize serial communication for monitoring
  Serial.begin(9600);
  
  // Initialize the OLED display
  u8x8.begin();
  u8x8.setPowerSave(0); // Disable power-saving mode
  
  // Initialize and set the clock to the compilation time
  clock.begin();
  clock.setDateTime(__DATE__, __TIME__);
  
  // Configure pins for button and red LED
  pinMode(ledRed, OUTPUT);
  pinMode(button, INPUT_PULLUP); // Enable internal pull-up resistor for the button
}

/*
   Checks if a measurement is available and keeps the state machine alive.
   Returns true if a new measurement is obtained.
*/
static bool measure_environment(float *temperature, float *humidity) {
  static unsigned long measurement_timestamp = millis();

  // Measure every 4 seconds
  if (millis() - measurement_timestamp > 3000ul) {
    if (dht_sensor.measure(temperature, humidity) == true) {
      measurement_timestamp = millis();
      return true;
    }
  }
  return false;
}

// Main program loop
void loop() {
  float temperature;
  float humidity;
  
  // Check if the button is pressed
  if (digitalRead(button) == HIGH) {
    // Measure environmental data
    if (measure_environment(&temperature, &humidity) == true) {
      if (temperature > maxTemperature) {
        maxTemperature = temperature;
      }
      
      // Display temperature, humidity, and time on the OLED display
      u8x8.setFont(u8x8_font_chroma48medium8_r);
      u8x8.setCursor(0, 1);
      Serial.print("T = ");
      u8x8.print("T = ");
      Serial.print(temperature, 1);
      u8x8.print(temperature);
      Serial.print("H = ");
      Serial.print(humidity, 1);
      Serial.println("%");
      
      u8x8.setCursor(0, 2);
      u8x8.print("MAX = ");
      u8x8.print(maxTemperature);
      
      // Display the current time
      u8x8.setCursor(0, 3);
      dt = clock.getDateTime();
      u8x8.print(dt.hour);
      u8x8.print(":");
      u8x8.print(dt.minute);
      u8x8.print(":");
      u8x8.print(dt.second);
      u8x8.println("");

      // Check if temperature exceeds 24°C and control the red LED accordingly
      if (temperature > 24) {
        digitalWrite(ledRed, HIGH); // Turn on red LED
      } else {
        digitalWrite(ledRed, LOW); // Turn off red LED
      }
    }
    
    // If the button is not pressed
    if (digitalRead(button) == LOW) {
      // Turn on the red LED and display "TEST" on OLED for 1 second
      digitalWrite(ledRed, HIGH);
      u8x8.setCursor(5, 5);
      u8x8.print("TEST");
      delay(1000);
      u8x8.clear(); // Clear the OLED display
    }
  }
}
