// Include all required libraries
#include <Wire.h>
#include <DS3231.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#include <Arduino.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <EEPROM.h>

// Component and pin declarations
DS3231 clock;
RTCDateTime dt;
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
float temperature;
float humidity;
int redLED = 7;
int potentiometer = A0;
U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
int maxTemp = 0;
int eepromAddress = sizeof(int);
int result;
int buttonClear = 8;
int buttonRead = 6;

// Function that measures temperature and humidity every 3 seconds
static bool measure_environment(float *temperature, float *humidity)
{
    static unsigned long measurement_timestamp = millis();

    /* Measure once every three seconds */
    if (millis() - measurement_timestamp > 3000ul)
    {
        if (dht_sensor.measure(temperature, humidity) == true)
        {
            measurement_timestamp = millis();
            return true;
        }
    }

    return false;
}

// Setup function runs once when the program starts
void setup()
{
    Serial.begin(9600);
    // Initialize RTC module
    clock.begin();
    // Set time and date based on compile time
    clock.setDateTime(__DATE__, __TIME__);
    // Define pins as input or output
    pinMode(redLED, OUTPUT);
    pinMode(potentiometer, INPUT);
    // Initialize OLED display
    u8x8.begin();
    u8x8.setPowerSave(0);
    // Test LED
    digitalWrite(redLED, HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    // Define buttons
    pinMode(buttonClear, INPUT_PULLUP);
    pinMode(buttonRead, INPUT_PULLUP);
}

void loop()
{
    // Set font for OLED display
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    // Read current time
    dt = clock.getDateTime();

    // Display time on OLED
    u8x8.setCursor(0, 0);
    u8x8.print("Time: ");
    u8x8.print(dt.hour);
    u8x8.print(":");
    u8x8.print(dt.minute);
    u8x8.print(":");
    u8x8.print(dt.second);

    // Measure temperature and humidity
    if (measure_environment(&temperature, &humidity))
    {
        // Display temperature and humidity on OLED
        u8x8.setCursor(0, 1);
        u8x8.print("Temp: ");
        u8x8.print(temperature);
        u8x8.print(" C");
        u8x8.setCursor(0, 2);
        u8x8.print("Humidity: ");
        u8x8.print(humidity);
        u8x8.print(" %");

        // Save temperature to EEPROM
        EEPROM.put(eepromAddress, temperature);
        eepromAddress += sizeof(int);

        // Save humidity to EEPROM
        EEPROM.put(eepromAddress, humidity);
        eepromAddress += sizeof(int);

        // Save hour to EEPROM
        EEPROM.put(eepromAddress, dt.hour);
        eepromAddress += sizeof(int);

        // Save minute to EEPROM
        EEPROM.put(eepromAddress, dt.minute);
        eepromAddress += sizeof(int);
    }

    // Read potentiometer
    int potValue = analogRead(potentiometer);
    // Map potentiometer value to range 20-30
    int thresholdTemp = map(potValue, 0, 1023, 20, 30);
    // Display threshold on OLED
    u8x8.setCursor(0, 4);
    u8x8.print("Threshold: ");
    u8x8.print(thresholdTemp);

    // Control red LED if temperature exceeds threshold
    if (temperature > thresholdTemp)
    {
        digitalWrite(redLED, HIGH);
    }
    else
    {
        digitalWrite(redLED, LOW);
    }

    // Display max temperature on OLED
    if (temperature > maxTemp)
    {
        u8x8.setCursor(0, 3);
        u8x8.print("Max Temp: ");
        maxTemp = temperature;
        u8x8.print(maxTemp);
        u8x8.print(" C");
    }

    // Clear EEPROM when buttonClear is pressed
    if (digitalRead(buttonClear) == LOW)
    {
        eepromAddress = 0;
        result = 0;
    }

    // Read EEPROM when buttonRead is pressed
    if (digitalRead(buttonRead) == LOW)
    {
        for (int i = sizeof(int); i < EEPROM.length(); i += sizeof(int))
        {
            EEPROM.get(i, result);
            Serial.println(result);
            result = 0;
        }
    }

    // Wait 1 second before next loop
    delay(1000);
}
