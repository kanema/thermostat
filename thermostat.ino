#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// pin 9 - Serial clock out (SCLK)
// pin 8 - Serial data out (DIN)
// pin 7 - Data/Command select (D/C)
// pin 6 - LCD chip select (CS/CE)
// pin 5 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 6, 5);

// DS18B20
#define ONE_WIRE_BUS 3

// Relay
#define RELAY 11

// Instance of sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Temp min and max.
float tempMin = 999;
float tempMax = 0;

// Relay config
int RELAY_DELAY = 31;
int RELAY_CICLES = RELAY_DELAY;
int RELAY_STATUS = HIGH;

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

float value = 0;
char buf[10];
int potentiometer = 0;

void setup()   
{
  Serial.begin(9600);

  // display init
  display.begin();
  display.setContrast(0);

  // sensor init
  sensors.begin();
  sensors.setWaitForConversion(true);

  // relay output
  pinMode(RELAY, OUTPUT);
}

void loop()
{
  // sensor read
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);

  Serial.println(tempC);
  
  // temp min and max refresh
  if (tempC > 0 && tempC < 100 && tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > 0 && tempC < 100 && tempC > tempMax)
  {
    tempMax = tempC;
  }

  // display reset
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  
  value = analogRead(potentiometer) / 32;
  
  display.print("Temp.: ");
  display.print(tempC);
  display.print("C");
  display.println();
  
  display.print("Req.:  ");
  display.print(value);
  display.print("C");
  display.println();
  
  display.print("Min:   ");
  display.print(tempMin);
  display.print("C");
  display.println();
  
  display.print("Max:   ");
  display.print(tempMax);
  display.print("C");
  display.println();

  if (RELAY_CICLES >= RELAY_DELAY)
  {
    if (tempC > value)
    {
      RELAY_STATUS = HIGH;
    }
    else
    {
      RELAY_STATUS = LOW;
    }
    digitalWrite(RELAY, RELAY_STATUS);
    RELAY_CICLES = 0;
  }

  display.print("Relay: ");
  if (RELAY_STATUS == HIGH)
  {
    display.print("On");
  }
  else
  {
    display.print("Off");
  }
  display.println();
  
  display.print("Next:  ");
  display.print(RELAY_DELAY - RELAY_CICLES);
  
  display.display();

  RELAY_CICLES++;
  delay(1000);
}
