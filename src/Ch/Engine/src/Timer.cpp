
#include "Timer.h"

namespace Advanced2D
{

Timer::Timer(void)
{
	timer_start = timeGetTime();
	reset();
}

Timer::~Timer(void)
{
}

DWORD Timer::getTimer()
{
	return timeGetTime();
}

DWORD Timer::getStartTimeMillis()
{
	return timeGetTime() - timer_start;
}

void Timer::sleep(int ms)
{
	DWORD start = getTimer();

	while (start + ms > getTimer());
}

void Timer::reset()
{
	stopwatch_start = getTimer();
}

bool Timer::stopwatch(int ms)
{
	if (timeGetTime() > stopwatch_start + ms)
	{
		stopwatch_start = getTimer();
		return true;
	}

	return false;
}

}
