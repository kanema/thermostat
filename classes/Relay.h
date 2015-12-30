#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay
{
  public:
    Relay(int pin);
    Relay(int pin, int delay);
    int getNext();
    void cicle();
    bool isNext();
    bool isOn();
    void set(bool status);
    void setOn();
    void setOff();
    void reset();
  private:
    int _delay;
    int _pin;
    int _cicles;
    bool _status;
};

#endif
