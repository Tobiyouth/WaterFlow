#ifndef WaterFlow_h
#define WaterFlow_h

#include "Arduino.h"


class WaterFlow
{
private:
  uint8_t _pin;
  volatile unsigned long _pulse;
  int _constant = 0;
  float _flowRateMinute;
  int _flowRateSecond;
  long _volume;
  long _timeBefore = 0;
  bool flowing = false;
  void (*_countFun)(void) ;

public:
  WaterFlow(uint8_t pin ,uint8_t constant);
  void begin(void (*userFunc)(void));
  void read();
  void pulseCount();
  float getFlowRateOfMinute();
  int getFlowRateOfSecond();
  long getVolume();
  bool isFlowing();
  void clearVolume();
};

#endif