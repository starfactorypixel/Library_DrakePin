#pragma once

#if defined(USE_HAL_DRIVER)
	#if defined(STM32F1)
		#include "stm32f1xx_hal.h"
	#elif defined(STM32H7)
		#include "stm32h7xx_hal.h"
	#endif
	
	#include "gpio_stm32.hpp"
#elif defined(ESP32)
	#include "driver/gpio.h"
	#include "driver/adc.h"
	#include "esp_adc_cal.h"
	
	#include "gpio_esp32.hpp"
#elif defined(AVR)
	#include "avr_gpio.hpp"
#else
	#error Unsupported platform
#endif
