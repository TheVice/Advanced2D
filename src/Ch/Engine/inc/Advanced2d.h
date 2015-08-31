#ifndef __ADVANCED2D_H_
#define __ADVANCED2D_H_

#include "Timer.h"
#include <string>
#include <tchar.h>
#include <d3dx9.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

namespace Advanced2D
{
class Engine
{
private:
	static unsigned short sVersionMajor;
	static unsigned short sVersionMinor;
	static unsigned short sRevision;

	static int sWidth;
	static int sHeight;
	static int sColorDepth;
	static bool sFullScreen;

#if UNICODE
	static std::wstring sTitle;
#else
	static std::string sTitle;
#endif

	const HWND mWindowHandle;

	LPDIRECT3D9 mDirect3d;
	LPDIRECT3DDEVICE9 mDirect3dDevice;
	LPDIRECT3DSURFACE9 mBackBuffer;
	LPD3DXSPRITE mSpriteHandler;
	D3DCOLOR mAmbientColor;

	bool mPause;
	bool mMaximizeProcessor;

	Timer mCoreTimer;
	long mFrameCountCore;
	long mFrameRateCore;

	Timer mRealTimer;
	long mFrameCountReal;
	long mFrameRateReal;

	Engine();
	Engine(const Engine& aRhs);
	Engine& operator=(const Engine& aRhs);
public:
	static unsigned short getVersionMajor();
	static unsigned short getVersionMinor();
	static unsigned short getRevision();
#if UNICODE
	static std::wstring getVersionText();
#else
	static std::string getVersionText();
#endif
	static int getScreenWidth();
	static void setScreenWidth(int aWidth);
	static int getScreenHeight();
	static void setScreenHeight(int aHeight);
	static int getColorDepth();
	static void setColorDepth(int aColorDepth);
	static bool getFullScreen();
	static void setFullScreen(bool aFullScreen);
	static void close();

	static const _TCHAR* getAppTitle();
	static void setAppTitle(const _TCHAR* aTitle);

	static void shutdown();

	static void showMessage(const _TCHAR* aMessage,
	                        const _TCHAR* aTitle = TEXT("ADVANCED 2D"));
	static void showFatalMessage(const _TCHAR* aMessage,
	                             const _TCHAR* aTitle = TEXT("FATAL ERROR"));

	Engine(HWND aWindowHandle);
	HWND getWindowHandle();

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getBackBuffer();
	LPD3DXSPRITE getSpriteHandler();

	bool isPaused();
	void setPaused(bool aPause);

	void clearScene(D3DCOLOR aColor);
	void setIdentity();
	void setDefaultMaterial();
	void setAmbient(D3DCOLOR aAmbientColor);

	int renderStart();
	int renderStop();

	long getFrameRate_core();
	long getFrameRate_real();

	bool getMaximizeProcessor();
	void setMaximizeProcessor(bool aMaximizeProcessor);

	void update();

	virtual ~Engine();
};
}

extern bool gameover;
extern bool game_preload();
extern bool game_init();
extern void game_update();
extern void game_end();
extern void game_render3d();

extern Advanced2D::Engine* g_engine;

#endif
