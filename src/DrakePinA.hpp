#pragma once
#include <inttypes.h>
#include "DrakePinTypes.hpp"
#include "platform/gpio_platforms.hpp"

namespace DrakePin
{
class PinA
{
	public:
		
		constexpr PinA(const PinA_t &pin, uint32_t sampling) : _pin(pin), _sampling(sampling)
		{}
		
		void Init()
		{
			platform_adc_init(_pin);
			Calibration();
		}
		
		void InitWithoutCalibration()
		{
			platform_adc_init(_pin);
		}
		
		uint32_t ReadRaw()
		{
			return platform_adc_read_raw(_pin, _sampling);
		}
		
		uint32_t ReadVol()
		{
			return platform_adc_read_mv(_pin, _sampling);
		}
		
		void Calibration()
		{
			platform_adc_calibration(_pin);
		}
		
	private:
		
		const PinA_t _pin;
		uint32_t _sampling;
		
};
}

using DrakePinA = DrakePin::PinA;
