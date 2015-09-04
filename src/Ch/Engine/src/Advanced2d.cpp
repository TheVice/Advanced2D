
#include "Advanced2D.h"
#include "Input.h"
#include <sstream>

namespace Advanced2D
{

unsigned short Engine::sVersionMajor = VERSION_MAJOR;
unsigned short Engine::sVersionMinor = VERSION_MINOR;
unsigned short Engine::sRevision = REVISION;
int Engine::sWidth = 640;
int Engine::sHeight = 480;
int Engine::sColorDepth = 32;
bool Engine::sFullScreen = false;

#if UNICODE
std::wstring Engine::sTitle;
#else
std::string Engine::sTitle;
#endif

unsigned short Engine::getVersionMajor()
{
	return sVersionMajor;
}

unsigned short Engine::getVersionMinor()
{
	return sVersionMinor;
}

unsigned short Engine::getRevision()
{
	return sRevision;
}

#if UNICODE
std::wstring Engine::getVersionText()
{
	std::wstringstream v;
	v << L"Advanced2D Engine v " << sVersionMajor << L"." << sVersionMinor << L"."
	  << sRevision;
	return v.str();
}
#else
std::string Engine::getVersionText()
{
	std::ostringstream v;
	v << "Advanced2D Engine v " << sVersionMajor << "." << sVersionMinor << "." <<
	  sRevision;
	return v.str();
}
#endif

int Engine::getScreenWidth()
{
	return sWidth;
}

void Engine::setScreenWidth(int aWidth)
{
	sWidth = aWidth;
}

int Engine::getScreenHeight()
{
	return sHeight;
}

void Engine::setScreenHeight(int aHeight)
{
	sHeight = aHeight;
}

int Engine::getColorDepth()
{
	return sColorDepth;
}

void Engine::setColorDepth(int aColorDepth)
{
	sColorDepth = aColorDepth;
}

bool Engine::getFullScreen()
{
	return sFullScreen;
}

void Engine::setFullScreen(bool aFullScreen)
{
	sFullScreen = aFullScreen;
}

void Engine::close()
{
	game_end();
}

const _TCHAR* Engine::getAppTitle()
{
	return sTitle.c_str();
}

void Engine::setAppTitle(const _TCHAR* aTitle)
{
#if UNICODE
	sTitle = std::wstring(aTitle);
#else
	sTitle = std::string(aTitle);
#endif
}

void Engine::shutdown()
{
	gameover = true;
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

void Engine::updateKeyboard()
{
	static unsigned char oldKeys[256];

	for (int n = 0; n < 255; ++n)
	{
		//check for key press
		if (mInput->getKeyState(n) & 0x80)
		{
			game_keyPress(n);
			oldKeys[n] = mInput->getKeyState(n);
		}
		//check for release
		else if (oldKeys[n] & 0x80)
		{
			game_keyRelease(n);
			oldKeys[n] = mInput->getKeyState(n);
		}
	}
}

void Engine::updateMouse()
{
	static int oldPosX = 0;
	static int oldPosY = 0;
	int deltaX = mInput->getDeltaX();
	int deltaY = mInput->getDeltaY();

	//check mouse buttons 1-3
	for (unsigned char n = 0; n < 4; ++n)
	{
		if (mInput->getMouseButton(n))
		{
			game_mouseButton(n);
		}
	}

	//check mouse position
	if (mInput->getPosX() != oldPosX || mInput->getPosY() != oldPosY)
	{
		game_mouseMove(oldPosX = mInput->getPosX(), oldPosY = mInput->getPosY());
	}

	//check mouse motion
	if (deltaX || deltaY)
	{
		game_mouseMotion(deltaX, deltaY);
	}

	//check mouse wheel
	int wheel = mInput->getDeltaWheel();

	if (wheel)
	{
		game_mouseWheel(wheel);
	}
}

Engine::Engine(HWND aWindowHandle) :
	mWindowHandle(aWindowHandle),
	mDirect3d(NULL),
	mDirect3dDevice(NULL),
	mBackBuffer(NULL),
	mSpriteHandler(NULL),
	mAmbientColor(D3DCOLOR_RGBA(255, 255, 255, 0)),
	mPause(false),
	mMaximizeProcessor(false),
	mCoreTimer(),
	mFrameCountCore(0),
	mFrameRateCore(0),
	mRealTimer(),
	mFrameCountReal(0),
	mFrameRateReal(0),
	mInput(NULL)
{
	mDirect3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!mDirect3d)
	{
		throw new std::exception();
	}

	D3DDISPLAYMODE displayMode;
	memset(&displayMode, 0, sizeof(D3DDISPLAYMODE));

	if (FAILED(mDirect3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &displayMode)))
	{
		throw new std::exception();
	}

	D3DPRESENT_PARAMETERS presentationParameters;
	memset(&presentationParameters, 0, sizeof(D3DPRESENT_PARAMETERS));
	presentationParameters.Windowed = (!Engine::getFullScreen());
	presentationParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentationParameters.EnableAutoDepthStencil = TRUE;
	presentationParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentationParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	presentationParameters.BackBufferFormat = displayMode.Format;
	presentationParameters.BackBufferCount = 1;
	presentationParameters.BackBufferWidth = Engine::getScreenWidth();
	presentationParameters.BackBufferHeight = Engine::getScreenHeight();
	presentationParameters.hDeviceWindow = mWindowHandle;

	if (FAILED(mDirect3d->CreateDevice(
	               D3DADAPTER_DEFAULT,
	               D3DDEVTYPE_HAL,
	               mWindowHandle,
	               D3DCREATE_HARDWARE_VERTEXPROCESSING,
	               &presentationParameters,
	               &mDirect3dDevice)))
	{
		throw new std::exception();
	}

	clearScene(D3DCOLOR_XRGB(0, 0, 0));

	//create pointer to BackBuffer
	if (FAILED(mDirect3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
	           &mBackBuffer)))
	{
		throw new std::exception();
	}

	//use ambient lighting and z-buffering
	if (FAILED(mDirect3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE)))
	{
		throw new std::exception();
	}

	if (FAILED(mDirect3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID)))
	{
		throw new std::exception();
	}

	if (FAILED(mDirect3dDevice->SetRenderState(D3DRS_LIGHTING, TRUE)))
	{
		throw new std::exception();
	}

	setAmbient(mAmbientColor);

	//initialize 2D render
	if (D3D_OK != D3DXCreateSprite(mDirect3dDevice, &mSpriteHandler))
	{
		throw new std::exception();
	}

	setDefaultMaterial();
	mInput = new Input(mWindowHandle);
}

HWND Engine::getWindowHandle()
{
	return mWindowHandle;
}

LPDIRECT3DDEVICE9 Engine::getDevice()
{
	return mDirect3dDevice;
}

LPDIRECT3DSURFACE9 Engine::getBackBuffer()
{
	return mBackBuffer;
}

LPD3DXSPRITE Engine::getSpriteHandler()
{
	return mSpriteHandler;
}

bool Engine::isPaused()
{
	return mPause;
}

void Engine::setPaused(bool aPause)
{
	mPause = aPause;
}

void Engine::clearScene(D3DCOLOR aColor)
{
	if (FAILED(mDirect3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	                                  aColor, 1.0f, 0)))
	{
		throw new std::exception();
	}
}

void Engine::setIdentity()
{
	D3DXMATRIX matrixWorld;
	D3DXMatrixIdentity(&matrixWorld);

	if (FAILED(mDirect3dDevice->SetTransform(D3DTS_WORLD, &matrixWorld)))
	{
		throw new std::exception();
	}
}

void Engine::setDefaultMaterial()
{
	D3DMATERIAL9 material;
	memset(&material, 0, sizeof(D3DMATERIAL9));
	material.Diffuse.r = material.Ambient.r = 1.0f;
	material.Diffuse.g = material.Ambient.g = 1.0f;
	material.Diffuse.b = material.Ambient.b = 1.0f;
	material.Diffuse.a = material.Ambient.a = 1.0f;

	if (FAILED(mDirect3dDevice->SetMaterial(&material)))
	{
		throw new std::exception();
	}
}

void Engine::setAmbient(D3DCOLOR aAmbientColor)
{
	mAmbientColor = aAmbientColor;

	if (FAILED(mDirect3dDevice->SetRenderState(D3DRS_AMBIENT, mAmbientColor)))
	{
		throw new std::exception();
	}
}

int Engine::renderStart()
{
	if (D3D_OK != mDirect3dDevice->BeginScene())
	{
		return 0;
	}

	return 1;
}

int Engine::renderStop()
{
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

int Engine::render2dStart()
{
	if (FAILED(mSpriteHandler->Begin(D3DXSPRITE_ALPHABLEND)))
	{
		return 0;
	}

	return 1;
}

int Engine::render2dStop()
{
	if (FAILED(mSpriteHandler->End()))
	{
		return 0;
	}

	return 1;
}

long Engine::getFrameRate_core()
{
	return mFrameCountCore;
}

long Engine::getFrameRate_real()
{
	return mFrameCountReal;
}

bool Engine::getMaximizeProcessor()
{
	return mMaximizeProcessor;
}

void Engine::setMaximizeProcessor(bool aMaximizeProcessor)
{
	mMaximizeProcessor = aMaximizeProcessor;
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

		//update input devices
		mInput->update();
		updateKeyboard();
		updateMouse();
		//begin rendering
		renderStart();
		//let game do it's own 3D
		game_render3d();
		//2D rendering
		render2dStart();
		game_render2d();
		render2dStop();
		//done rendering
		renderStop();
	}
}

Engine::~Engine()
{
	delete mInput;
	mInput = NULL;

	if (mDirect3dDevice)
	{
		mDirect3dDevice->Release();
	}

	if (mDirect3d)
	{
		mDirect3d->Release();
	}
}

}
