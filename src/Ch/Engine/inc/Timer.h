#ifndef __TIMER_H_
#define __TIMER_H_

#include <windows.h>

namespace Advanced2D
{
class Timer
{
private:
	DWORD mStart;
	DWORD mStopWatchStart;

	Timer(const Timer& aRhs);
	Timer& operator=(const Timer& aRhs);
public:
	Timer();
	static DWORD getTimer();
	DWORD getStartTimeMillis();
	void sleep(int aMillis);
	void reset();
	bool stopwatch(int aMillis);
	virtual ~Timer();
};
}

#endif
