
#include "Advanced2D.h"
#include <stdio.h>

namespace Advanced2D
{

Engine::Engine() :
	mVersionMajor(VERSION_MAJOR),
	mVersionMinor(VERSION_MINOR),
	mRevision(REVISION),
	mWindowHandle(HWND_DESKTOP),
	mDirect3d(NULL),
	mDirect3dDevice(NULL),
	mBackbuffer(NULL),
	mSpriteHandler(NULL),
	mFullScreen(false),
	mWidth(640),
	mHeight(480),
	mColorDepth(32),
	mPause(false),
	mAmbientColor(D3DCOLOR_RGBA(255, 255, 255, 0)),
	mMaximizeProcessor(false),
	mFrameCountCore(0),
	mFrameRateCore(0),
	mFrameCountReal(0),
	mFrameRateReal(0)
{
	setAppTitle(TEXT("Advanced2D"));
}

Engine::~Engine()
{
	if (mDirect3dDevice)
	{
		mDirect3dDevice->Release();
	}

	if (mDirect3d)
	{
		mDirect3d->Release();
	}
}

_TCHAR* Engine::getVersionText(_TCHAR* aVersion)
{
#if _MSC_VER > 1310
	_stprintf_s(aVersion, 64 * sizeof(_TCHAR), TEXT("Advanced2D Engine v %i.%i.%i"),
	            mVersionMajor,
	            mVersionMinor, mRevision);
#else
	_stprintf(aVersion, TEXT("Advanced2D Engine v %i.%i.%i"), mVersionMajor,
	          mVersionMinor, mRevision);
#endif
	return aVersion;
}

void Engine::showMessage(const _TCHAR* aMessage, const _TCHAR* aTitle)
{
	MessageBox(NULL, aMessage, aTitle, MB_OK);
}

void Engine::showFatalMessage(const _TCHAR* aMessage, const _TCHAR* aTitle)
{
	showMessage(aMessage, aTitle);
	shutdown();
}

int Engine::init(int aWidth, int aHeight, int/*aColorDepth*/, bool aFullScreen)
{
	mDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!mDirect3d)
	{
		return 0;
	}

	D3DDISPLAYMODE dm;
	memset(&dm, 0, sizeof(D3DDISPLAYMODE));
	mDirect3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = (!aFullScreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferFormat = dm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = aWidth;
	d3dpp.BackBufferHeight = aHeight;
	d3dpp.hDeviceWindow = mWindowHandle;
	mDirect3d->CreateDevice(
	    D3DADAPTER_DEFAULT,
	    D3DDEVTYPE_HAL,
	    mWindowHandle,
	    D3DCREATE_HARDWARE_VERTEXPROCESSING,
	    &d3dpp,
	    &mDirect3dDevice);

	if (!mDirect3dDevice)
	{
		return 0;
	}

	clearScene(D3DCOLOR_XRGB(0, 0, 0));
	//create pointer to BackBuffer
	mDirect3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
	                               &mBackbuffer);
	//use ambient lighting and z-buffering
	mDirect3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	mDirect3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	mDirect3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	setAmbient(mAmbientColor);

	//initialize 2D render
	if (D3D_OK != D3DXCreateSprite(mDirect3dDevice, &mSpriteHandler))
	{
		return 0;
	}

	if (!game_init(getWindowHandle()))
	{
		return 0;
	}

	setDefaultMaterial();
	return 1;
}

void Engine::setDefaultMaterial()
{
	D3DMATERIAL9 mat;
	memset(&mat, 0, sizeof(D3DMATERIAL9));
	mat.Diffuse.r = mat.Ambient.r = 1.0f;
	mat.Diffuse.g = mat.Ambient.g = 1.0f;
	mat.Diffuse.b = mat.Ambient.b = 1.0f;
	mat.Diffuse.a = mat.Ambient.a = 1.0f;
	mDirect3dDevice->SetMaterial(&mat);
}

void Engine::clearScene(D3DCOLOR aColor)
{
	mDirect3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	                       aColor,
	                       1.0f,
	                       0);
}

void Engine::setAmbient(D3DCOLOR aColor)
{
	mAmbientColor = aColor;
	mDirect3dDevice->SetRenderState(D3DRS_AMBIENT, mAmbientColor);
}

int Engine::renderStart()
{
	if (!mDirect3dDevice)
	{
		return 0;
	}

	if (D3D_OK != mDirect3dDevice->BeginScene())
	{
		return 0;
	}

	return 1;
}

int Engine::renderStop()
{
	if (!mDirect3dDevice)
	{
		return 0;
	}

	if (D3D_OK != mDirect3dDevice->EndScene())
	{
		return 0;
	}

	if (D3D_OK != mDirect3dDevice->Present(NULL, NULL, NULL, NULL))
	{
		return 0;
	}

	return 1;
}

void Engine::shutdown()
{
	gameover = true;
}

void Engine::update()
{
	static Timer timedUpdate;
	//calculate core framerate
	mFrameCountCore++;

	if (mCoreTimer.stopwatch(999))
	{
		mFrameRateCore = mFrameCountCore;
		mFrameCountCore = 0;
	}

	//fast update with no timing
	game_update();

	//update with 60fps timing
	if (!timedUpdate.stopwatch(14))
	{
		if (!getMaximizeProcessor())
		{
			Sleep(1);
		}
	}
	else
	{
		//calculate real framerate
		mFrameCountReal++;

		if (mRealTimer.stopwatch(999))
		{
			mFrameRateReal = mFrameCountReal;
			mFrameCountReal = 0;
		}

		//begin rendering
		renderStart();
		//done rendering
		renderStop();
	}
}

void Engine::close()
{
	game_end();
}

bool Engine::isPaused()
{
	return mPause;
}

void Engine::setPauser(bool aPause)
{
	mPause = aPause;
}

LPDIRECT3DDEVICE9 Engine::getDevice()
{
	return mDirect3dDevice;
}

LPDIRECT3DSURFACE9 Engine::getBackBuffer()
{
	return mBackbuffer;
}

LPD3DXSPRITE Engine::getSpriteHandler()
{
	return mSpriteHandler;
}

void Engine::setWindowHandle(HWND aHwnd)
{
	mWindowHandle = aHwnd;
}

HWND Engine::getWindowHandle()
{
	return mWindowHandle;
}

_TCHAR* Engine::getAppTitle(_TCHAR* aTitle)
{
	if (!aTitle)
	{
		return mTitle;
	}

#if _MSC_VER > 1310
	_tcscpy_s(aTitle, 64, mTitle);
#else
	_tcscpy(aTitle, mTitle);
#endif
	return aTitle;
}

void Engine::setAppTitle(const _TCHAR* aTitle)
{
#if _MSC_VER > 1310
	_tcsncpy_s(mTitle, 64, aTitle,
	           sizeof(mTitle) / sizeof(*mTitle));
#else
	_tcsncpy(mTitle, aTitle, sizeof(mTitle) / sizeof(*mTitle));
#endif
}

unsigned short Engine::getVersionMajor()
{
	return mVersionMajor;
}

unsigned short Engine::getVersionMinor()
{
	return mVersionMinor;
}

unsigned short Engine::getRevision()
{
	return mRevision;
}

long Engine::getFrameRate_core()
{
	return mFrameCountCore;
}

long Engine::getFrameRate_real()
{
	return mFrameCountReal;
}

int Engine::getScreenWidth()
{
	return mWidth;
}

void Engine::setScreenWidth(int aWidth)
{
	mWidth = aWidth;
}

int Engine::getScreenHeight()
{
	return mHeight;
}

void Engine::setScreenHeight(int aHeight)
{
	mHeight = aHeight;
}

int Engine::getColorDepth()
{
	return mColorDepth;
}

void Engine::setColorDepth(int aColorDepth)
{
	mColorDepth = aColorDepth;
}

bool Engine::getFullScreen()
{
	return mFullScreen;
}

void Engine::setFullScreen(bool aFullScreen)
{
	mFullScreen = aFullScreen;
}

bool Engine::getMaximizeProcessor()
{
	return mMaximizeProcessor;
}

void Engine::setMaximizeProcessor(bool aMaximizeProcessor)
{
	mMaximizeProcessor = aMaximizeProcessor;
}

}
