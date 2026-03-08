#pragma once
#include <inttypes.h>

namespace DrakePin
{
	struct PinD_t
	{
		void *port;
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
		void *handle;
		void *port;
		uint32_t pin;
		uint32_t channel;
	};
}
