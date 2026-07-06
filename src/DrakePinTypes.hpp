#pragma once
#include <inttypes.h>
#include "platform/gpio_platform_types.hpp"

namespace DrakePin
{
	struct PinD_t
	{
		GpioPort_t port;
		uint32_t pin;
	};
	
	enum ModeD_t
	{
		Disable,
		Input,
		InputPullup,
		InputPulldown,
		Output,
		OutputOpenDrain,
	};
	
	enum LevelD_t
	{
		Low = 0,
		High = 1,
		HiZ = 2,
	};
	
	struct PinA_t
	{
		AdcHandle_t handle;
		GpioPort_t port;
		uint32_t pin;
		uint32_t channel;
	};
}
