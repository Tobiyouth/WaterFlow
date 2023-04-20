## Description
   
Arduino library for Flow Sensor.   


### Flowrate Formula   
The SensorConstant is different for different models.
```math
Q = Frequency / SensorConstant 
```
Q = Flowrate (Liter/minute)   


## Usages

### initialization
```cpp
#include <WaterFlow.h>

//SensorConstant is 65
WaterFlow waterFlow(PIN2, 65);
```

### Sensor begin
param **`userFunc`** 
```cpp

void count() {
  waterFlow.pulseCount();
}

//The begin function must be called from the setup function
void setup() {
  waterFlow.begin(count);
}
```

### Sensor Read
```cpp
//The read function must be called from the loop function
void loop() {
  waterFlow.read();
}
```


### Get Flowrate (L/m)
return **`Flowrate`** (L/m)
```cpp
float getFlowRateOfMinute() 
```


### Get Flowrate (mL/s)
return **`Flowrate`** (mL/s)
```cpp
int getFlowRateOfSecond() 
```

### Get Total Volume (mL)
return **`Volume`** (mL)
```cpp
long getVolume()
```  


### Clear Total Volume
```cpp
void clearVolume()
```  


### Determine if it is flowing
return true or false
```cpp
bool isFlowing()
```  


### Start and stop the listener
```cpp
void setListeners(void (*start)(void), void (*stop)(void));
```  

### Example

```cpp
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

```