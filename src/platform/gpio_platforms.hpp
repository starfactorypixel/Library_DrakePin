#pragma once
#include "gpio_platform_types.hpp"

#if defined(USE_HAL_DRIVER)
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
