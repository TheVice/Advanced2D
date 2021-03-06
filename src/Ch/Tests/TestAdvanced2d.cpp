
#include "Advanced2D.h"
#include <gtest/gtest.h>

bool game_preload()
{
	return true;
}

bool game_init()
{
	return true;
}

void game_update()
{
}

void game_entityUpdate(Advanced2D::Entity*)
{
}

void game_entityRender(Advanced2D::Entity*)
{
}

void game_entityCollision(Advanced2D::Entity*, Advanced2D::Entity*)
{
}

void game_keyPress(int)
{
}

void game_keyRelease(int)
{
}

void game_mouseButton(int)
{
}

void game_mouseMotion(int, int)
{
}

void game_mouseMove(int, int)
{
}

void game_mouseWheel(int)
{
}

void game_render2d()
{
}

void game_render3d()
{
}

void game_end()
{
}

TEST(TestAdvanced2D_Static, getVersionMajor)
{
	ASSERT_EQ(1, Advanced2D::Engine::getVersionMajor());
}

TEST(TestAdvanced2D_Static, getVersionMinor)
{
	ASSERT_EQ(0, Advanced2D::Engine::getVersionMinor());
}

TEST(TestAdvanced2D_Static, getRevision)
{
	ASSERT_EQ(0, Advanced2D::Engine::getRevision());
}

TEST(TestAdvanced2D_Static, getVersionText)
{
	ASSERT_STRNE(TEXT(""), Advanced2D::Engine::getVersionText().c_str());
}

TEST(TestAdvanced2D_Static, getScreenWidth)
{
	ASSERT_EQ(640, Advanced2D::Engine::getScreenWidth());
}

TEST(TestAdvanced2D_Static, setScreenWidth)
{
	ASSERT_EQ(640, Advanced2D::Engine::getScreenWidth());
	Advanced2D::Engine::setScreenWidth(320);
	ASSERT_EQ(320, Advanced2D::Engine::getScreenWidth());
}

TEST(TestAdvanced2D_Static, getScreenHeight)
{
	ASSERT_EQ(480, Advanced2D::Engine::getScreenHeight());
}

TEST(TestAdvanced2D_Static, setScreenHeight)
{
	ASSERT_EQ(480, Advanced2D::Engine::getScreenHeight());
	Advanced2D::Engine::setScreenHeight(240);
	ASSERT_EQ(240, Advanced2D::Engine::getScreenHeight());
}

TEST(TestAdvanced2D_Static, getColorDepth)
{
	ASSERT_EQ(32, Advanced2D::Engine::getColorDepth());
}

TEST(TestAdvanced2D_Static, setColorDepth)
{
	ASSERT_EQ(32, Advanced2D::Engine::getColorDepth());
	Advanced2D::Engine::setColorDepth(16);
	ASSERT_EQ(16, Advanced2D::Engine::getColorDepth());
}

TEST(TestAdvanced2D_Static, getFullScreen)
{
	ASSERT_FALSE(Advanced2D::Engine::getFullScreen());
}

TEST(TestAdvanced2D_Static, setFullScreen)
{
	bool currentState = Advanced2D::Engine::getFullScreen();
	Advanced2D::Engine::setFullScreen(!currentState);
	ASSERT_EQ(!currentState, Advanced2D::Engine::getFullScreen());
}

TEST(TestAdvanced2D_Static, close)
{
	Advanced2D::Engine::close();
}

TEST(TestAdvanced2D_Static, getAppTitle)
{
	ASSERT_STREQ(TEXT(""), Advanced2D::Engine::getAppTitle());
}

TEST(TestAdvanced2D_Static, setAppTitle)
{
	ASSERT_STREQ(TEXT(""), Advanced2D::Engine::getAppTitle());
	Advanced2D::Engine::setAppTitle(TEXT("TestAdvanced2d"));
	ASSERT_STREQ(TEXT("TestAdvanced2d"), Advanced2D::Engine::getAppTitle());
}

TEST(TestAdvanced2D_Static, shutdown)
{
	Advanced2D::Engine::shutdown();
}
#ifdef ENABLED
TEST(TestAdvanced2D_Static, showMessage)
{
	Advanced2D::Engine::showMessage("showMessage");
	//Sleep(2500);
	//SendMessage(FindWindow("#32770", NULL), WM_CLOSE, 0, 0);
}

TEST(TestAdvanced2D_Static, showFatalMessage)
{
	Advanced2D::Engine::showFatalMessage("showFatalMessage");
}
#endif

bool gameover = false;
Advanced2D::Engine* g_engine = NULL;

class TestAdvanced2D : public testing::Test
{
#define CLASS_NAME TEXT("TestAdvanced2D")
private:
	static LRESULT WINAPI WinProc(HWND aHwnd, UINT aMsg, WPARAM aWparam,
	                              LPARAM aLparam)
	{
		switch (aMsg)
		{
			case WM_QUIT:
			case WM_CLOSE:
			case WM_DESTROY:
				Advanced2D::Engine::shutdown();
				break;
		}

		return DefWindowProc(aHwnd, aMsg, aWparam, aLparam);
	}

	static HWND MakeWindow(HINSTANCE aInstance, int aWidth, int aHeight)
	{
		WNDCLASSEX wc;
		memset(&wc, 0, sizeof(WNDCLASSEX));
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = WinProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = aInstance;
		wc.hIcon = NULL;
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = NULL;
		wc.lpszMenuName = NULL;
		wc.lpszClassName = CLASS_NAME;
		wc.hIconSm = NULL;
		//
		RegisterClassEx(&wc);
		//
		DWORD dwStyle = WS_OVERLAPPEDWINDOW;
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		//
		RECT windowRect;
		windowRect.left = 0L;
		windowRect.right = aWidth;
		windowRect.top = 0L;
		windowRect.bottom = aHeight;
		AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
		//
		HWND hwnd = CreateWindowEx(0, wc.lpszClassName,
		                           TEXT("TEST"), dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		                           0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
		                           HWND_DESKTOP, NULL, aInstance, NULL);
		return hwnd;
	}
protected:
	TestAdvanced2D()
	{
		g_engine = NULL;
	}
	virtual void SetUp()
	{
		Advanced2D::Engine::setFullScreen(false);
		HWND hwnd = MakeWindow(GetModuleHandle(NULL), 640, 480);
		g_engine = new Advanced2D::Engine(hwnd);
	}
	virtual void TearDown()
	{
		UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
		delete g_engine;
	}
	virtual ~TestAdvanced2D()
	{
		g_engine = NULL;
	}
};

TEST_F(TestAdvanced2D, getWindowHandle)
{
	ASSERT_NE(HWND_DESKTOP, g_engine->getWindowHandle());
}

TEST_F(TestAdvanced2D, getDevice)
{
	ASSERT_TRUE(g_engine->getDevice());
}

TEST_F(TestAdvanced2D, getBackBuffer)
{
	ASSERT_TRUE(g_engine->getBackBuffer());
}

TEST_F(TestAdvanced2D, getSpriteHandler)
{
	ASSERT_TRUE(g_engine->getSpriteHandler());
}

TEST_F(TestAdvanced2D, isPaused)
{
	ASSERT_FALSE(g_engine->isPaused());
}

TEST_F(TestAdvanced2D, setPaused)
{
	ASSERT_FALSE(g_engine->isPaused());
	g_engine->setPaused(true);
	ASSERT_TRUE(g_engine->isPaused());
}

TEST_F(TestAdvanced2D, clearScene)
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 0));
}

TEST_F(TestAdvanced2D, setIdentity)
{
	g_engine->setIdentity();
}

TEST_F(TestAdvanced2D, setDefaultMaterial)
{
	g_engine->setDefaultMaterial();
}

TEST_F(TestAdvanced2D, setAmbient)
{
	g_engine->setAmbient(D3DCOLOR_RGBA(255, 255, 255, 0));
}

TEST_F(TestAdvanced2D, renderStart)
{
	g_engine->renderStart();
}

TEST_F(TestAdvanced2D, renderStop)
{
	g_engine->renderStop();
}

TEST_F(TestAdvanced2D, getFrameRate_core)
{
	ASSERT_EQ(0, g_engine->getFrameRate_core());
}

TEST_F(TestAdvanced2D, getFrameRate_real)
{
	ASSERT_EQ(0, g_engine->getFrameRate_real());
}

TEST_F(TestAdvanced2D, getMaximizeProcessor)
{
	ASSERT_FALSE(g_engine->getMaximizeProcessor());
}

TEST_F(TestAdvanced2D, setMaximizeProcessor)
{
	ASSERT_FALSE(g_engine->getMaximizeProcessor());
	g_engine->setMaximizeProcessor(true);
	ASSERT_TRUE(g_engine->getMaximizeProcessor());
}

TEST_F(TestAdvanced2D, update)
{
	ASSERT_EQ(0, g_engine->getFrameRate_core());
	ASSERT_EQ(0, g_engine->getFrameRate_real());
	g_engine->update();
	Sleep(25);
	g_engine->update();
	ASSERT_NE(0, g_engine->getFrameRate_core());
	ASSERT_NE(0, g_engine->getFrameRate_real());
}
