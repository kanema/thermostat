
#include "Relay.h"
#include "Arduino.h"

Relay::Relay(int pin, int delay)
{
  _pin = pin;
  _delay = delay;
  _cicles = _delay;
  setOn();
}

int Relay::getNext()
{
  return _delay - _cicles;
}

void Relay::cicle()
{
  _cicles++;
}

bool Relay::isNext()
{
  return _cicles >= _delay;
}

bool Relay::isOn()
{
  return _status == HIGH;
}

void Relay::set(bool status)
{
  _status = status;
  pinMode(_pin, _status);
}

void Relay::setOn()
{
  set(HIGH);
}

void Relay::setOff()
{
  set(LOW);
}

void Relay::reset()
{
  _cicles = 0;
}

