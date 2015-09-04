
#include "Timer.h"

namespace Advanced2D
{

Timer::Timer()
{
	mStart = getTimer();
	reset();
}

DWORD Timer::getTimer()
{
	return timeGetTime();
}

DWORD Timer::getStartTimeMillis()
{
	return getTimer() - mStart;
}

void Timer::sleep(int aMillis)
{
	DWORD start = getTimer();

	while (start + aMillis > getTimer());
}

void Timer::reset()
{
	mStopWatchStart = getTimer();
}

bool Timer::stopwatch(int aMillis)
{
	if (getTimer() > mStopWatchStart + aMillis)
	{
		mStopWatchStart = getTimer();
		return true;
	}

	return false;
}

Timer::~Timer()
{
}

}
