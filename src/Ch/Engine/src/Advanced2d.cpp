
#include "Advanced2D.h"
#include <stdio.h>
#include <time.h>

namespace Advanced2D
{

Engine::Engine() : p_versionMajor(VERSION_MAJOR), p_versionMinor(VERSION_MINOR),
	p_revision(REVISION),  p_windowHandle(HWND_DESKTOP), p_d3d(NULL),
	p_device(NULL), p_backbuffer(NULL), p_sprite_handler(NULL),
	p_fullscreen(false), p_screenwidth(640), p_screenheight(480),
	p_colordepth(32), p_pauseMode(false),
	p_ambientColor(D3DCOLOR_RGBA(255, 255, 255, 0)),
	p_maximizeProcessor(false), p_frameCount_core(0), p_frameRate_core(0),
	p_frameCount_real(0),
	p_frameRate_real(0)
{
	srand((unsigned int)time(NULL));
	this->setAppTitle(TEXT("Advanced2D"));
}

Engine::~Engine()
{
	if (this->p_device)
	{
		this->p_device->Release();
	}

	if (this->p_d3d)
	{
		this->p_d3d->Release();
	}
}

_TCHAR* Engine::getVersionText(_TCHAR* szDest)
{
#if _MSC_VER > 1310
	_stprintf_s(szDest, 64 * sizeof(_TCHAR), TEXT("Advanced2D Engine v %i.%i.%i"),
	            p_versionMajor,
	            p_versionMinor, p_revision);
#else
	_stprintf(szDest, TEXT("Advanced2D Engine v %i.%i.%i"), p_versionMajor,
	          p_versionMinor, p_revision);
#endif
	return szDest;
}

void Engine::message(const _TCHAR* message, const _TCHAR* title)
{
	MessageBox(NULL, message, title, MB_OK);
}

void Engine::fatalerror(const _TCHAR* message, const _TCHAR* title)
{
	this->message(message, title);
	Shutdown();
}

int Engine::Init(int width, int height, int/*colordepth*/, bool fullscreen)
{
	this->p_d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (NULL == this->p_d3d)
	{
		return 0;
	}

	D3DDISPLAYMODE dm;
	memset(&dm, 0, sizeof(D3DDISPLAYMODE));
	this->p_d3d->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));
	d3dpp.Windowed = (!fullscreen);
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.BackBufferFormat = dm.Format;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.hDeviceWindow = p_windowHandle;
	this->p_d3d->CreateDevice(
	    D3DADAPTER_DEFAULT,
	    D3DDEVTYPE_HAL,
	    this->p_windowHandle,
	    D3DCREATE_HARDWARE_VERTEXPROCESSING,
	    &d3dpp,
	    &this->p_device);

	if (NULL == this->p_device)
	{
		return 0;
	}

	this->ClearScene(D3DCOLOR_XRGB(0, 0, 0));
	//create pointer to BackBuffer
	this->p_device->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO,
	                              &this->p_backbuffer);
	//use ambient lighting and z-buffering
	this->p_device->SetRenderState(D3DRS_ZENABLE, TRUE);
	this->p_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	this->p_device->SetRenderState(D3DRS_LIGHTING, true);
	this->SetAmbient(this->p_ambientColor);

	//initialize 2D render
	if (D3D_OK != D3DXCreateSprite(this->p_device, &this->p_sprite_handler))
	{
		return 0;
	}

	if (!game_init(this->getWindowHandle()))
	{
		return 0;
	}

	SetDefaultMaterial();
	return 1;
}

void Engine::SetDefaultMaterial()
{
	D3DMATERIAL9 mat;
	memset(&mat, 0, sizeof(D3DMATERIAL9));
	mat.Diffuse.r = mat.Ambient.r = 1.0f;
	mat.Diffuse.g = mat.Ambient.g = 1.0f;
	mat.Diffuse.b = mat.Ambient.b = 1.0f;
	mat.Diffuse.a = mat.Ambient.a = 1.0f;
	p_device->SetMaterial(&mat);
}

void Engine::ClearScene(D3DCOLOR color)
{
	this->p_device->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, color, 1.0f,
	                      0);
}

void Engine::SetAmbient(D3DCOLOR color)
{
	this->p_ambientColor = color;
	this->p_device->SetRenderState(D3DRS_AMBIENT, this->p_ambientColor);
}

int Engine::RenderStart()
{
	if (!this->p_device)
	{
		return 0;
	}

	if (D3D_OK != this->p_device->BeginScene())
	{
		return 0;
	}

	return 1;
}

int Engine::RenderStop()
{
	if (!this->p_device)
	{
		return 0;
	}

	if (D3D_OK != this->p_device->EndScene())
	{
		return 0;
	}

	if (D3D_OK != p_device->Present(NULL, NULL, NULL, NULL))
	{
		return 0;
	}

	return 1;
}

void Engine::Shutdown()
{
	gameover = true;
}

void Engine::Update()
{
	static Timer timedUpdate;
	//calculate core framerate
	p_frameCount_core++;

	if (p_coreTimer.stopwatch(999))
	{
		p_frameRate_core = p_frameCount_core;
		p_frameCount_core = 0;
	}

	//fast update with no timing
	game_update();

	//update with 60fps timing
	if (!timedUpdate.stopwatch(14))
	{
		if (!this->getMaximizeProcessor())
		{
			Sleep(1);
		}
	}
	else
	{
		//calculate real framerate
		p_frameCount_real++;

		if (p_realTimer.stopwatch(999))
		{
			p_frameRate_real = p_frameCount_real;
			p_frameCount_real = 0;
		}

		//begin rendering
		this->RenderStart();
		//done rendering
		this->RenderStop();
	}
}

void Engine::Close()
{
	game_end();
}

bool Engine::isPaused()
{
	return this->p_pauseMode;
}

void Engine::setPauser(bool value)
{
	this->p_pauseMode = value;
}

LPDIRECT3DDEVICE9 Engine::getDevice()
{
	return this->p_device;
}

LPDIRECT3DSURFACE9 Engine::getBackBuffer()
{
	return this->p_backbuffer;
}

LPD3DXSPRITE Engine::getSpriteHandler()
{
	return this->p_sprite_handler;
}

void Engine::setWindowHandle(HWND hWnd)
{
	this->p_windowHandle = hWnd;
}

HWND Engine::getWindowHandle()
{
	return this->p_windowHandle;
}

_TCHAR* Engine::getAppTitle(_TCHAR* value)
{
	if (NULL == value)
	{
		return this->p_apptitle;
	}

#if _MSC_VER > 1310
	_tcscpy_s(value, 64, this->p_apptitle);
#else
	_tcscpy(value, this->p_apptitle);
#endif
	return value;
}

void Engine::setAppTitle(const _TCHAR* value)
{
#if _MSC_VER > 1310
	_tcsncpy_s(this->p_apptitle, 64, value,
	           sizeof(p_apptitle) / sizeof(*p_apptitle));
#else
	_tcsncpy(this->p_apptitle, value, sizeof(p_apptitle) / sizeof(*p_apptitle));
#endif
}

unsigned short Engine::getVersionMajor()
{
	return this->p_versionMajor;
}

unsigned short Engine::getVersionMinor()
{
	return this->p_versionMinor;
}

unsigned short Engine::getRevision()
{
	return this->p_revision;
}

long Engine::getFrameRate_core()
{
	return this->p_frameCount_core;
}

long Engine::getFrameRate_real()
{
	return this->p_frameCount_real;
}

int Engine::getScreenWidth()
{
	return this->p_screenwidth;
}

void Engine::setScreenWidth(int value)
{
	this->p_screenwidth = value;
}

int Engine::getScreenHeight()
{
	return this->p_screenheight;
}

void Engine::setScreenHeight(int value)
{
	this->p_screenheight = value;
}

int Engine::getColorDepth()
{
	return this->p_colordepth;
}

void Engine::setColorDepth(int value)
{
	this->p_colordepth = value;
}

bool Engine::getFullScreen()
{
	return this->p_fullscreen;
}

void Engine::setFullScreen(bool value)
{
	this->p_fullscreen = value;
}

bool Engine::getMaximizeProcessor()
{
	return this->p_maximizeProcessor;
}

void Engine::setMaximizeProcessor(bool value)
{
	this->p_maximizeProcessor = value;
}

}
