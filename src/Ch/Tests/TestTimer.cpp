
#include "Timer.h"
#include <gtest/gtest.h>

class Timer : public testing::Test
{
public:
	Advanced2D::Timer* timer;
protected:
	Timer() : timer(NULL)
	{
	}
	virtual void SetUp()
	{
		timer = new Advanced2D::Timer();
	}
	virtual void TearDown()
	{
		delete timer;
	}
	virtual ~Timer()
	{
		timer = NULL;
	}
};

TEST_F(Timer, getStartTimeMillis_sleep)
{
	ASSERT_GT(50, timer->getStartTimeMillis());
	timer->sleep(550);
	ASSERT_LT(500, timer->getStartTimeMillis());
}

TEST_F(Timer, reset_stopwatch)
{
	ASSERT_FALSE(timer->stopwatch(50));
	timer->sleep(55);
	ASSERT_TRUE(timer->stopwatch(50));
	ASSERT_FALSE(timer->stopwatch(50));
}
