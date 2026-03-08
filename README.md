# DrakePin

### STM32
```cpp
#include <DrakePinD.hpp>
#include <DrakePinA.hpp>

ADC_HandleTypeDef hadc1;

DrakePinD pin1({GPIOA, GPIO_PIN_3}, DrakePin::Output, DrakePin::High);
DrakePinD pin2({GPIOA, GPIO_PIN_4}, DrakePin::Output, DrakePin::High);
DrakePinD pin3({GPIOB, GPIO_PIN_5}, DrakePin::OutputOpenDrain, DrakePin::Low);
DrakePinD pin4({GPIOB, GPIO_PIN_6}, DrakePin::OutputOpenDrain, DrakePin::Low);
DrakePinA adc1({&hadc1, GPIOA, GPIO_PIN_0, ADC_CHANNEL_1}, ADC_SAMPLETIME_1CYCLE_5);
```

### ESP32
```cpp
#include "Arduino.h"

DrakePinD pin1({0, GPIO_NUM_3}, DrakePin::Output, DrakePin::High);
DrakePinD pin2({0, GPIO_NUM_4}, DrakePin::Output, DrakePin::High);
DrakePinD pin3({0, GPIO_NUM_5}, DrakePin::OutputOpenDrain, DrakePin::Low);
DrakePinD pin4({0, GPIO_NUM_6}, DrakePin::OutputOpenDrain, DrakePin::Low);
DrakePinA adc1({0, 0, 0, ADC1_CHANNEL_1}, 0);											
```
