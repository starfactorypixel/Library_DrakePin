#pragma once
#include <inttypes.h>
#include "DrakePinTypes.hpp"

namespace DrakePin
{
	inline void platform_io_write(const PinD_t &pin, LevelD_t level);

	inline void platform_io_init(const PinD_t &pin, ModeD_t mode, LevelD_t level)
	{
		GPIO_InitTypeDef i = {pin.pin, GPIO_MODE_INPUT, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH};
		switch(mode)
		{
			case ModeD_t::Input:
			{
				break;
			}
			case ModeD_t::InputPullup:
			{
				i.Pull = GPIO_PULLUP; break;
			}
			case ModeD_t::Disable:
			case ModeD_t::InputPulldown:
			{
				i.Pull = GPIO_PULLDOWN; break;
			}
			case ModeD_t::Output:
			{
				i.Mode = GPIO_MODE_OUTPUT_PP; break;
			}
			case ModeD_t::OutputOpenDrain:
			{
				i.Mode = GPIO_MODE_OUTPUT_OD; break;
			}
		}
		HAL_GPIO_Init((GPIO_TypeDef *)pin.port, &i);
		platform_io_write(pin, level);
		
		return;
	}

	inline void platform_io_mode(const PinD_t &pin, ModeD_t mode, LevelD_t level)
	{
		platform_io_init(pin, mode, level);
		
		return;
	}

	inline void platform_io_write(const PinD_t &pin, LevelD_t level)
	{
		if(level == LevelD_t::HiZ) return;
		
		HAL_GPIO_WritePin((GPIO_TypeDef *)pin.port, pin.pin, ((level == LevelD_t::High) ? GPIO_PIN_SET : GPIO_PIN_RESET));
		
		return;
	}

	inline void platform_io_toggle(const PinD_t &pin)
	{
		HAL_GPIO_TogglePin((GPIO_TypeDef *)pin.port, pin.pin);
		
		return;
	}
	
	inline LevelD_t platform_io_read(const PinD_t &pin)
	{
		return HAL_GPIO_ReadPin((GPIO_TypeDef *)pin.port, pin.pin) ? LevelD_t::High : LevelD_t::Low;
	}
	
	
	inline void platform_adc_init(const PinA_t &pin)
	{
		GPIO_InitTypeDef i = {pin.pin, GPIO_MODE_ANALOG, GPIO_NOPULL, GPIO_SPEED_FREQ_HIGH};
		HAL_GPIO_Init((GPIO_TypeDef *)pin.port, &i);
		HAL_ADC_Start((ADC_HandleTypeDef *)pin.handle);
		
		return;
	}

	inline uint32_t platform_adc_read_raw(const PinA_t &pin, uint32_t sampling)
	{
		ADC_ChannelConfTypeDef c = {pin.channel, ADC_REGULAR_RANK_1, sampling};
		HAL_ADC_ConfigChannel((ADC_HandleTypeDef *)pin.handle, &c);
		HAL_ADC_Start((ADC_HandleTypeDef *)pin.handle);
		HAL_ADC_PollForConversion((ADC_HandleTypeDef *)pin.handle, 10);
		return HAL_ADC_GetValue((ADC_HandleTypeDef *)pin.handle);
	}
	
	inline uint32_t platform_adc_read_mv(const PinA_t &pin, uint32_t sampling)
	{
		uint32_t raw = platform_adc_read_raw(pin, sampling);
		uint32_t mv = (raw * 3300) / 4095;
		
		return mv;
	}
	
	inline void platform_adc_calibration(const PinA_t &pin)
	{
		HAL_ADC_Stop((ADC_HandleTypeDef *)pin.handle);
		#if defined(STM32F1)
		HAL_ADCEx_Calibration_Start((ADC_HandleTypeDef *)pin.handle);
		#elif defined(STM32H7)
		HAL_ADCEx_Calibration_Start((ADC_HandleTypeDef *)pin.handle, ADC_CALIB_OFFSET, ADC_SINGLE_ENDED);
		#endif
		HAL_ADC_Start((ADC_HandleTypeDef *)pin.handle);
		return;
	}
}
