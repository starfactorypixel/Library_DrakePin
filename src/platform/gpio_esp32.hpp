#pragma once
#include <inttypes.h>
#include "DrakePinTypes.hpp"

namespace DrakePin
{
	inline void platform_io_write(const PinD_t &pin, LevelD_t level);
	inline void platform_adc_calibration(const PinA_t &pin);

	inline void platform_io_init(const PinD_t &pin, ModeD_t mode, LevelD_t level)
	{
		gpio_mode_t m;
		switch(mode)
		{
			case ModeD_t::Disable:
			{
				m = GPIO_MODE_DISABLE; break;
			}
			case ModeD_t::Input:
			case ModeD_t::InputPullup:
			case ModeD_t::InputPulldown:
			{
				m = GPIO_MODE_INPUT; break;
			}
			case ModeD_t::Output:
			{
				m = GPIO_MODE_OUTPUT; break;
			}
			case ModeD_t::OutputOpenDrain:
			{
				m = GPIO_MODE_OUTPUT_OD; break;
			}
		}
		
		gpio_config_t conf = { (BIT(pin.pin)), m, GPIO_PULLUP_DISABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE };
		if(mode == ModeD_t::InputPullup) conf.pull_up_en = GPIO_PULLUP_ENABLE;
		if(mode == ModeD_t::InputPulldown) conf.pull_down_en = GPIO_PULLDOWN_ENABLE;
		gpio_config(&conf);
		platform_io_write(pin, level);
		
		return;
	}

	inline void platform_io_mode(const PinD_t &pin, ModeD_t mode, LevelD_t level)
	{
		gpio_mode_t m;
		gpio_pull_mode_t p;
		switch(mode)
		{
			case ModeD_t::Input:
			{
				m = GPIO_MODE_INPUT;
				p = GPIO_FLOATING;
				break;
			}
			case ModeD_t::InputPullup:
			{
				m = GPIO_MODE_INPUT;
				p = GPIO_PULLUP_ONLY;
				break;
			}
			case ModeD_t::InputPulldown:
			{
				m = GPIO_MODE_INPUT;
				p = GPIO_PULLDOWN_ONLY;
				break;
			}
			case ModeD_t::Output:
			{
				m = GPIO_MODE_OUTPUT;
				p = GPIO_FLOATING;
				break;
			}
			case ModeD_t::OutputOpenDrain:
			{
				m = GPIO_MODE_OUTPUT_OD;
				p = GPIO_FLOATING;
				break;
			}
			default:
			{
				m = GPIO_MODE_DISABLE;
				p = GPIO_FLOATING;
				break;
			}
		}
		gpio_set_direction((gpio_num_t)pin.pin, m);
		gpio_set_pull_mode((gpio_num_t)pin.pin, p);
		platform_io_write(pin, level);
		
		return;
	}

	inline void platform_io_write(const PinD_t &pin, LevelD_t level)
	{
		if(level == LevelD_t::HiZ) return;
		
		gpio_set_level((gpio_num_t)pin.pin, level);

		return;
	}

	inline void platform_io_toggle(const PinD_t &pin)
	{
		int v = gpio_get_level((gpio_num_t)pin.pin);
		gpio_set_level((gpio_num_t)pin.pin, (1 - v));

		return;
	}

	inline LevelD_t platform_io_read(const PinD_t &pin)
	{
		return gpio_get_level((gpio_num_t)pin.pin) ? LevelD_t::High : LevelD_t::Low;
	}
	
	
	esp_adc_cal_characteristics_t adc_chars;
	
	inline void platform_adc_init(const PinA_t &pin)
	{
		adc1_config_width(ADC_WIDTH_BIT_12);
		adc1_config_channel_atten((adc1_channel_t)pin.channel, ADC_ATTEN_DB_12);
		platform_adc_calibration(pin);
		
		return;
	}

	inline uint32_t platform_adc_read_raw(const PinA_t &pin, uint32_t sampling)
	{
		return adc1_get_raw((adc1_channel_t)pin.channel);
	}
	
	inline uint32_t platform_adc_read_mv(const PinA_t &pin, uint32_t sampling)
	{
		uint32_t raw = platform_adc_read_raw(pin, sampling);
		uint32_t mv = esp_adc_cal_raw_to_voltage(raw, &adc_chars);
		
		return mv;
	}

	inline void platform_adc_calibration(const PinA_t &pin)
	{
		esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_12, ADC_WIDTH_BIT_12, 1100, &adc_chars);
		
		return;
	}
}
