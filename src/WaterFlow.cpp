#include "Arduino.h"
#include "WaterFlow.h"

/**
* @param pin flow sensor pin
* @param sensorConstant The constant of the sensor is different for different models.
*/
WaterFlow::WaterFlow(uint8_t pin, uint8_t sensorConstant) {
  _pin = pin;
  _constant = sensorConstant;
}



void WaterFlow::pulseCount() {
  if(!flowing && _start){
    _start();
  }

  this->_pulse++;
  this->flowing = true;
}


void WaterFlow::begin(void (*userFunc)(void)) {
  _countFun = userFunc;
  pinMode(this->_pin, INPUT);
  digitalWrite(this->_pin, INPUT_PULLUP);                                
  attachInterrupt(digitalPinToInterrupt(this->_pin), _countFun, FALLING);  
}


void WaterFlow::read() {
  if ((millis() - _timeBefore) > 1000) {
    if (_pulse == 0) {
       if(flowing && _stop){
          _stop();
        }

      flowing = false;
      return;
    }

    detachInterrupt(digitalPinToInterrupt(this->_pin));

    _flowRateMinute = ((1000.0 / (millis() - _timeBefore)) * _pulse) / _constant;
    _flowRateSecond = (_flowRateMinute / 60) * 1000;  

    _volume += _flowRateSecond;

    _timeBefore = millis();
    _pulse = 0;

    attachInterrupt(digitalPinToInterrupt(this->_pin), _countFun, FALLING);
  }
}


/**
 * 
 * @return flow rate L / minute
 */
float WaterFlow::getFlowRateOfMinute() {
  return this->_flowRateMinute;
}



/**
 * 
 * @return flow rate mL / scond
 */
int WaterFlow::getFlowRateOfSecond() {
  return this->_flowRateSecond;
}

long WaterFlow::getVolume() {
  return this->_volume;
}


bool WaterFlow::isFlowing(){
  return this->flowing;
}

void WaterFlow::clearVolume(){
  this->_volume = 0;
}

/**
 *  Set up start and stop listeners as needed.
 *
 *  @param start Called when the sensor is started, nullable.
 *  @param stop Called when the sensor stops, nullable.
 */
void WaterFlow::setListeners(void (*start)(void), void (*stop)(void)){
  this->_start = start;
  this->_stop = stop;
}