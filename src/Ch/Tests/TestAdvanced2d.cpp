
#include "Advanced2D.h"
#include <gtest/gtest.h>

bool game_preload()
{
	return true;
}

bool game_init(Advanced2D::Engine*)
{
	return true;
}

void game_update()
{
}

void game_end()
{
}

TEST(TestAdvanced2D, getVersionMajor)
{
	ASSERT_EQ(1, Advanced2D::Engine::getVersionMajor());
}

TEST(TestAdvanced2D, getVersionMinor)
{
	ASSERT_EQ(0, Advanced2D::Engine::getVersionMinor());
}

TEST(TestAdvanced2D, getRevision)
{
	ASSERT_EQ(0, Advanced2D::Engine::getRevision());
}

TEST(TestAdvanced2D, getVersionText)
{
	ASSERT_STRNE(TEXT(""), Advanced2D::Engine::getVersionText().c_str());
}

TEST(TestAdvanced2D, getScreenWidth)
{
	ASSERT_EQ(640, Advanced2D::Engine::getScreenWidth());
}

TEST(TestAdvanced2D, setScreenWidth)
{
	ASSERT_EQ(640, Advanced2D::Engine::getScreenWidth());
	Advanced2D::Engine::setScreenWidth(320);
	ASSERT_EQ(320, Advanced2D::Engine::getScreenWidth());
}

TEST(TestAdvanced2D, getScreenHeight)
{
	ASSERT_EQ(480, Advanced2D::Engine::getScreenHeight());
}

TEST(TestAdvanced2D, setScreenHeight)
{
	ASSERT_EQ(480, Advanced2D::Engine::getScreenHeight());
	Advanced2D::Engine::setScreenHeight(240);
	ASSERT_EQ(240, Advanced2D::Engine::getScreenHeight());
}

TEST(TestAdvanced2D, getColorDepth)
{
	ASSERT_EQ(32, Advanced2D::Engine::getColorDepth());
}

TEST(TestAdvanced2D, setColorDepth)
{
	ASSERT_EQ(32, Advanced2D::Engine::getColorDepth());
	Advanced2D::Engine::setColorDepth(16);
	ASSERT_EQ(16, Advanced2D::Engine::getColorDepth());
}

TEST(TestAdvanced2D, getFullScreen)
{
	ASSERT_FALSE(Advanced2D::Engine::getFullScreen());
}

TEST(TestAdvanced2D, setFullScreen)
{
	bool currentState = Advanced2D::Engine::getFullScreen();
	Advanced2D::Engine::setFullScreen(!currentState);
	ASSERT_EQ(!currentState, Advanced2D::Engine::getFullScreen());
}

TEST(TestAdvanced2D, close)
{
	Advanced2D::Engine::close();
}

TEST(TestAdvanced2D, getAppTitle)
{
	ASSERT_STREQ(TEXT(""), Advanced2D::Engine::getAppTitle());
}

TEST(TestAdvanced2D, setAppTitle)
{
	ASSERT_STREQ(TEXT(""), Advanced2D::Engine::getAppTitle());
	Advanced2D::Engine::setAppTitle(TEXT("TestAdvanced2d"));
	ASSERT_STREQ(TEXT("TestAdvanced2d"), Advanced2D::Engine::getAppTitle());
}

TEST(TestAdvanced2D, shutdown)
{
	Advanced2D::Engine::shutdown();
}
#ifdef ENABLED
TEST(TestAdvanced2D, showMessage)
{
	Advanced2D::Engine::showMessage("showMessage");
	//Sleep(2500);
	//SendMessage(FindWindow("#32770", NULL), WM_CLOSE, 0, 0);
}

TEST(TestAdvanced2D, showFatalMessage)
{
	Advanced2D::Engine::showFatalMessage("showFatalMessage");
}

TEST_F(TestAdvanced2D, getWindowHandle)
{
}

TEST_F(TestAdvanced2D, getDevice)
{
}

TEST_F(TestAdvanced2D, getBackBuffer)
{
}

TEST_F(TestAdvanced2D, getSpriteHandler)
{
}

TEST_F(TestAdvanced2D, isPaused)
{
}

TEST_F(TestAdvanced2D, setPaused)
{
}

TEST_F(TestAdvanced2D, clearScene)
{
}

TEST_F(TestAdvanced2D, setDefaultMaterial)
{
}

TEST_F(TestAdvanced2D, setAmbient)
{
}

TEST_F(TestAdvanced2D, renderStart)
{
}

TEST_F(TestAdvanced2D, renderStop)
{
}

TEST_F(TestAdvanced2D, getFrameRate_core)
{
}

TEST_F(TestAdvanced2D, getFrameRate_real)
{
}

TEST_F(TestAdvanced2D, getMaximizeProcessor)
{
}

TEST_F(TestAdvanced2D, setMaximizeProcessor)
{
}

TEST_F(TestAdvanced2D, update)
{
}
#endif
