#pragma once

#if defined(USE_HAL_DRIVER)
	#if defined(STM32F1)
		#include "stm32f1xx_hal.h"
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"
	#else
		#error Unsupported STM32 family
	#endif

namespace DrakePin
{
	using GpioPort_t = GPIO_TypeDef *;
	using AdcHandle_t = ADC_HandleTypeDef *;
}
#elif defined(ESP32)
namespace DrakePin
{
	using GpioPort_t = void *;
	using AdcHandle_t = void *;
}
#elif defined(AVR)
namespace DrakePin
{
	using GpioPort_t = void *;
	using AdcHandle_t = void *;
}
#else
	#error Unsupported platform
#endif
