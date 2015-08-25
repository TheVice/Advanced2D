#ifndef __TIMER_H_
#define __TIMER_H_

#include <windows.h>

namespace Advanced2D
{
class Timer
{
private:
	DWORD timer_start;
	DWORD stopwatch_start;
public:
	Timer(void);
	~Timer(void);
	DWORD getTimer();
	DWORD getStartTimeMillis();
	void sleep(int ms);
	void reset();
	bool stopwatch(int ms);
};
}

#endif
