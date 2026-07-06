#pragma once

namespace DrakePin
{
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
