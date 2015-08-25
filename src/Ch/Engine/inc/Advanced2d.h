#ifndef __ADVANCED2D_H_
#define __ADVANCED2D_H_

#include "Timer.h"
#include <TCHAR.H>
#include <d3dx9.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

extern bool gameover;
extern bool game_preload();
extern bool game_init(HWND);
extern void game_update();
extern void game_end();
extern void game_render3d();

namespace Advanced2D
{
class Engine
{
private:
	unsigned short p_versionMajor, p_versionMinor, p_revision;
	HWND p_windowHandle;
	LPDIRECT3D9 p_d3d;
	LPDIRECT3DDEVICE9 p_device;
	LPDIRECT3DSURFACE9 p_backbuffer;
	LPD3DXSPRITE p_sprite_handler;
	_TCHAR p_apptitle[MAX_PATH];
	bool p_fullscreen;
	int p_screenwidth;
	int p_screenheight;
	int p_colordepth;
	bool p_pauseMode;
	D3DCOLOR p_ambientColor;
	bool p_maximizeProcessor;
	Timer p_coreTimer;
	long p_frameCount_core;
	long p_frameRate_core;
	Timer p_realTimer;
	long p_frameCount_real;
	long p_frameRate_real;

public:
	Engine();
	virtual ~Engine();
	int Init(int width, int height, int colordepth, bool fullscreen);
	void Close();
	void Update();
	void message(const _TCHAR* message, const _TCHAR* title = TEXT("ADVANCED 2D"));
	void fatalerror(const _TCHAR* message,
	                const _TCHAR* title = TEXT("FATAL ERROR"));
	void Shutdown();
	void ClearScene(D3DCOLOR color);
	void SetDefaultMaterial();
	void SetAmbient(D3DCOLOR colorvalue);
	int RenderStart();
	int RenderStop();
	int Release();

	bool isPaused();
	void setPauser(bool value);

	LPDIRECT3DDEVICE9 getDevice();

	LPDIRECT3DSURFACE9 getBackBuffer();

	LPD3DXSPRITE getSpriteHandler();

	void setWindowHandle(HWND hWnd);
	HWND getWindowHandle();

	_TCHAR* getAppTitle(_TCHAR* value = NULL);
	void setAppTitle(const _TCHAR* value);

	unsigned short getVersionMajor();
	unsigned short getVersionMinor();
	unsigned short getRevision();
	_TCHAR* getVersionText(_TCHAR*);

	long getFrameRate_core();
	long getFrameRate_real();

	int getScreenWidth();
	void setScreenWidth(int value);
	int getScreenHeight();
	void setScreenHeight(int value);

	int getColorDepth();
	void setColorDepth(int value);

	bool getFullScreen();
	void setFullScreen(bool value);

	bool getMaximizeProcessor();
	void setMaximizeProcessor(bool value);

};
}

extern Advanced2D::Engine* g_engine;

#endif
