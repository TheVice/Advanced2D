#ifndef __ADVANCED2D_H_
#define __ADVANCED2D_H_

#include "Timer.h"
#include <tchar.h>
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
	unsigned short mVersionMajor, mVersionMinor, mRevision;
	HWND mWindowHandle;
	LPDIRECT3D9 mDirect3d;
	LPDIRECT3DDEVICE9 mDirect3dDevice;
	LPDIRECT3DSURFACE9 mBackbuffer;
	LPD3DXSPRITE mSpriteHandler;
	_TCHAR mTitle[MAX_PATH];
	bool mFullScreen;
	int mWidth;
	int mHeight;
	int mColorDepth;
	bool mPause;
	D3DCOLOR mAmbientColor;
	bool mMaximizeProcessor;
	Timer mCoreTimer;
	long mFrameCountCore;
	long mFrameRateCore;
	Timer mRealTimer;
	long mFrameCountReal;
	long mFrameRateReal;

public:
	Engine();
	virtual ~Engine();
	int init(int aWidth, int aHeight, int aColorDepth, bool aFullScreen);
	void close();
	void update();
	void showMessage(const _TCHAR* aMessage,
	                 const _TCHAR* aTitle = TEXT("ADVANCED 2D"));
	void showFatalMessage(const _TCHAR* aMessage,
	                      const _TCHAR* aTitle = TEXT("FATAL ERROR"));
	void shutdown();
	void clearScene(D3DCOLOR aColor);
	void setDefaultMaterial();
	void setAmbient(D3DCOLOR aColor);
	int renderStart();
	int renderStop();

	bool isPaused();
	void setPauser(bool aPause);

	LPDIRECT3DDEVICE9 getDevice();

	LPDIRECT3DSURFACE9 getBackBuffer();

	LPD3DXSPRITE getSpriteHandler();

	void setWindowHandle(HWND aHwnd);
	HWND getWindowHandle();

	_TCHAR* getAppTitle(_TCHAR* aTitle = NULL);
	void setAppTitle(const _TCHAR* aTitle);

	unsigned short getVersionMajor();
	unsigned short getVersionMinor();
	unsigned short getRevision();
	_TCHAR* getVersionText(_TCHAR* aVersion);

	long getFrameRate_core();
	long getFrameRate_real();

	int getScreenWidth();
	void setScreenWidth(int aWidth);
	int getScreenHeight();
	void setScreenHeight(int aHeight);

	int getColorDepth();
	void setColorDepth(int aColorDepth);

	bool getFullScreen();
	void setFullScreen(bool aFullScreen);

	bool getMaximizeProcessor();
	void setMaximizeProcessor(bool aMaximizeProcessor);

};
}

extern Advanced2D::Engine* g_engine;

#endif
