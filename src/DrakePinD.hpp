#pragma once
#include <inttypes.h>
#include "DrakePinTypes.hpp"
#include "platform/gpio_platforms.hpp"

using namespace DrakePin;

class DrakePinD
{
	public:
		
		constexpr DrakePinD(const PinD_t &pin, ModeD_t mode, LevelD_t level) : _pin(pin), _mode(mode), _level(level)
		{}
		
		void Init()
		{
			platform_io_init(_pin, _mode, _level);
		}
		
		void Mode(ModeD_t mode, LevelD_t level)
		{
			_mode = mode;
			_level = level;
			platform_io_mode(_pin, _mode, _level);
		}
		
		void On()
		{
			_level = LevelD_t::High;
			platform_io_write(_pin, _level);
		}
		
		void Off()
		{
			_level = LevelD_t::Low;
			platform_io_write(_pin, _level);
		}

		void Write(LevelD_t level)
		{
			_level = level;
			platform_io_write(_pin, _level);
		}
		
		void Toggle()
		{
			// Если LevelD_t::HiZ то переключится в High
			_level = ((_level == LevelD_t::High) ? LevelD_t::Low : LevelD_t::High);
			platform_io_toggle(_pin);
		}
		
		LevelD_t Read()
		{
			_level = platform_io_read(_pin);
			return _level;
		}
		
		LevelD_t GetLevel()
		{
			return _level;
		}
		
	private:
		
		const PinD_t &_pin;
		ModeD_t _mode;
		LevelD_t _level;
		
};
