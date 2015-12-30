#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "classes/Relay.h";

Relay *relay;

// pin 9 - Serial clock out (SCLK)
// pin 8 - Serial data out (DIN)
// pin 7 - Data/Command select (D/C)
// pin 6 - LCD chip select (CS/CE)
// pin 5 - LCD reset (RST)

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 8, 7, 6, 5);

// DS18B20
#define ONE_WIRE_BUS 3

// Instance of sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Temp min and max.
float tempMin = 999;
float tempMax = 0;

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
  relay = new Relay(13, 31);
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

  if (relay->isNext())
  {
    if (tempC > value)
    {
      relay->setOn();
    }
    else
    {
      relay->setOff();
    }
    relay->reset();
  }

  display.print("Relay: ");
  if (relay->isOn())
  {
    display.print("On");
  }
  else
  {
    display.print("Off");
  }
  display.println();
  
  display.print("Next:  ");
  display.print(relay->getNext());
  
  display.display();
  
  relay->cicle();
  delay(1000);
}
