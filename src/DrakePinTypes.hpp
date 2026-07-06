#pragma once
#include <inttypes.h>
#include "platform/gpio_platform_types.hpp"

namespace DrakePin
{
#if defined(ESP32)
	struct PinD_t
	{
		uint32_t pin;
	};

	struct PinA_t
	{
		uint32_t channel;
	};
#else
	struct PinD_t
	{
		GpioPort_t port;
		uint32_t pin;
	};

	struct PinA_t
	{
		AdcHandle_t handle;
		GpioPort_t port;
		uint32_t pin;
		uint32_t channel;
	};
#endif

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
}
