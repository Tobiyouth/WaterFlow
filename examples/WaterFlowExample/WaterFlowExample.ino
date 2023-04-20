#include "WaterFlow.h"

WaterFlow waterFlow(PIN2, 65);

unsigned long beforeTime;

void count() {
  waterFlow.pulseCount();
}

//Make a sound when starting or stopping.
void buzz(){
   tone(3, 800, 500);
}

void setup() {
  waterFlow.begin(count);
  waterFlow.setListeners(buzz, buzz);

  Serial.begin(9600);
}

void loop() {
  waterFlow.read();

  if ((millis() - beforeTime) >= 1000){
    beforeTime = millis();

    if(!waterFlow.isFlowing()){
      waterFlow.clearVolume();
      return;
    }

    Serial.print(waterFlow.getFlowRateOfMinute());
    Serial.print(" L/m   ");

    Serial.print(waterFlow.getFlowRateOfSecond());
    Serial.print(" mL/s   ");

    Serial.print(waterFlow.getVolume());
    Serial.println(" mL");
  }
}
