
#include "Timer.h"
#include <gtest/gtest.h>

class Timer : public testing::Test
{
public:
	Advanced2D::Timer* mTimer;
protected:
	Timer() : mTimer(NULL)
	{
	}
	virtual void SetUp()
	{
		mTimer = new Advanced2D::Timer();
	}
	virtual void TearDown()
	{
		delete mTimer;
	}
	virtual ~Timer()
	{
		mTimer = NULL;
	}
};

TEST_F(Timer, getStartTimeMillis_sleep)
{
	ASSERT_GT(50u, mTimer->getStartTimeMillis());
	mTimer->sleep(550);
	ASSERT_LT(500u, mTimer->getStartTimeMillis());
}

TEST_F(Timer, reset_stopwatch)
{
	ASSERT_FALSE(mTimer->stopwatch(50));
	mTimer->sleep(55);
	ASSERT_TRUE(mTimer->stopwatch(50));
	ASSERT_FALSE(mTimer->stopwatch(50));
}
