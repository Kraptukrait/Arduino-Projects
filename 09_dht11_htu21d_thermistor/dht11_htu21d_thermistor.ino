#include <Arduino.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11
#include <HTU21D.h>

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );
HTU21D sensor;

int tempPin = 0;

void setup(void)
{
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  sensor.begin();
}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if ( millis( ) - measurement_timestamp > 3000ul )
  {
    Serial.print( "Measurement: " );
    if ( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return ( true );
    }
  }
  Serial.println( "false " );
  return ( false );
}

void loop(void)
{
  float temperature;
  float humidity;

  if ( measure_environment( &temperature, &humidity ) == true )
  {
    u8x8.setCursor(0, 1);
    u8x8.print("DHT11 = ");
    u8x8.print(temperature);
    u8x8.print(" C");
  }

  if (sensor.measure()) {
    float temperature1 = sensor.getTemperature();
    u8x8.setCursor(0, 2);
    u8x8.print("GY = ");
    u8x8.print(temperature1);
    u8x8.print(" C");
  }

  int tempReading = analogRead(tempPin);
  double tempK = log(10000.0 * ((1024.0 / tempReading - 1)));
  tempK = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * tempK * tempK )) * tempK );
  float tempC = tempK - 273.15;
  u8x8.setCursor(0, 3);
  u8x8.print("Therm = ");
  u8x8.print(tempC);
  u8x8.print(" C");
}
