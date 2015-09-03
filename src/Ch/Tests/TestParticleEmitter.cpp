
#include "Advanced2D.h"
#include "ParticleEmitter.h"
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

void game_render3d()
{
}

void game_render2d()
{
}

void game_end()
{
}

class TestParticleEmitter : public testing::Test
{
#define CLASS_NAME TEXT("TestParticleEmitter")
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
public:
	Advanced2D::Engine* mEngine;
	Advanced2D::ParticleEmitter* mParticleEmitter;
protected:
	TestParticleEmitter() : mEngine(NULL), mParticleEmitter(NULL)
	{
	}
	virtual void SetUp()
	{
		Advanced2D::Engine::setFullScreen(false);
		HWND hwnd = MakeWindow(GetModuleHandle(NULL), 640, 480);
		mEngine = new Advanced2D::Engine(hwnd);
		g_engine = mEngine;
		mParticleEmitter = new Advanced2D::ParticleEmitter();
	}
	virtual void TearDown()
	{
		delete mParticleEmitter;
		UnregisterClass(CLASS_NAME, GetModuleHandle(NULL));
		delete mEngine;
	}
	virtual ~TestParticleEmitter()
	{
		mParticleEmitter = NULL;
		mEngine = NULL;
		g_engine = NULL;
	}
};

TEST_F(TestParticleEmitter, setPosition2D)
{
	mParticleEmitter->setPosition2D(Advanced2D::Vector3<float>(1.0f, 2.0f, 0.0f));
	ASSERT_EQ(Advanced2D::Vector3<float>(1.0f, 2.0f, 0.0f),
	          mParticleEmitter->getPosition());
	mParticleEmitter->setPosition2D(3.0f, 4.0f);
	ASSERT_EQ(Advanced2D::Vector3<float>(3.0f, 4.0f, 0.0f),
	          mParticleEmitter->getPosition());
}

TEST_F(TestParticleEmitter, getPosition)
{
	ASSERT_EQ(Advanced2D::Vector3<float>(), mParticleEmitter->getPosition());
}

TEST_F(TestParticleEmitter, setDirection)
{
	mParticleEmitter->setDirection(1.0f);
	ASSERT_FLOAT_EQ(1.0f, mParticleEmitter->getDirection());
	mParticleEmitter->setDirection(-1.0f);
	ASSERT_FLOAT_EQ(-1.0f, mParticleEmitter->getDirection());
}

TEST_F(TestParticleEmitter, getDirection)
{
	ASSERT_FLOAT_EQ(0.0f, mParticleEmitter->getDirection());
}

TEST_F(TestParticleEmitter, setMax)
{
	mParticleEmitter->setMax(10);
}

TEST_F(TestParticleEmitter, setAlphaRange)
{
	mParticleEmitter->setAlphaRange(254, 255);
}

TEST_F(TestParticleEmitter, setColorRange)
{
	mParticleEmitter->setColorRange(254, 254, 254, 255, 255, 255);
}

TEST_F(TestParticleEmitter, setSpread)
{
	mParticleEmitter->setSpread(10);
}

TEST_F(TestParticleEmitter, setLength)
{
	mParticleEmitter->setLength(10);
}

TEST_F(TestParticleEmitter, setVelocity)
{
	mParticleEmitter->setVelocity(0.1f);
}

TEST_F(TestParticleEmitter, setScale)
{
	mParticleEmitter->setScale(1.5f);
}

TEST_F(TestParticleEmitter, loadImage)
{
	mParticleEmitter->loadImage(TEXT("particle16.tga"));
}

TEST_F(TestParticleEmitter, draw)
{
	mParticleEmitter->draw();
}

TEST_F(TestParticleEmitter, update)
{
	mParticleEmitter->update();
}

TEST_F(TestParticleEmitter, add)
{
	mParticleEmitter->add();
}
