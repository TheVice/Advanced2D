#ifndef __ADVANCED2D_H_
#define __ADVANCED2D_H_

#include "Timer.h"
#ifdef MULTI_THREAD_ENGINE
#include "pthread_wrapper.h"
#endif
#include <string>
#include <list>
#include <tchar.h>
#include <d3dx9.h>

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define REVISION 0

namespace Advanced2D
{
class Input;
class Audio;
class Entity;
class Sprite;
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

	Input* mInput;
	void updateKeyboard();
	void updateMouse();

	Audio* mAudio;

	void updateEntities();
	void draw2DEntities();
	void draw3DEntities();
	void buryEntities();

#ifndef MULTI_THREAD_ENGINE
	std::list<Entity*> mEntities;
#else
	std::list<Entity*>* mEntities;
#endif

	Timer mCollisionTimer;

	bool collision(Sprite* aSprite1, Sprite* aSprite2);
	bool collisionBR(Sprite* aSprite1, Sprite* aSprite2);
	bool collisionD(Sprite* aSprite1, Sprite* aSprite2);
	void testForCollisions2D();

#ifdef MULTI_THREAD_ENGINE
	Timer mTimerUpdate;
	pthread_t m_thread_bury_entities;
#endif

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
#ifdef MULTI_THREAD_ENGINE
	pthread_mutex_t mMutex;
#endif

	Engine(HWND aWindowHandle);
	HWND getWindowHandle();

	LPDIRECT3DDEVICE9 getDevice();
	LPDIRECT3DSURFACE9 getBackBuffer();
	LPD3DXSPRITE getSpriteHandler();

	bool isPaused();
	void setPaused(bool aPause);

	Audio* getAudio() const;

	void clearScene(D3DCOLOR aColor);
	void setIdentity();
	void setDefaultMaterial();
	void setAmbient(D3DCOLOR aAmbientColor);

	int renderStart();
	int renderStop();
	int render2dStart();
	int render2dStop();

	long getFrameRate_core();
	long getFrameRate_real();

	bool getMaximizeProcessor();
	void setMaximizeProcessor(bool aMaximizeProcessor);

	void update();

	std::list<Entity*>* getEntityList();
	void addEntity(Entity* aEntity);
	Entity* findEntity(const _TCHAR* aEntityName);
	Entity* findEntity(int aEntityType);

	virtual ~Engine();
};
#ifdef MULTI_THREAD_ENGINE
void* thread_function_bury_entities(void* aData);
#endif
}

extern bool gameover;
extern bool game_preload();
extern bool game_init();
extern void game_update();
extern void game_entityUpdate(Advanced2D::Entity*);
extern void game_entityRender(Advanced2D::Entity*);
extern void game_entityCollision(Advanced2D::Entity*, Advanced2D::Entity*);
extern void game_keyPress(int);
extern void game_keyRelease(int);
extern void game_mouseButton(int);
extern void game_mouseMotion(int, int);
extern void game_mouseMove(int, int);
extern void game_mouseWheel(int);
extern void game_render2d();
extern void game_render3d();
extern void game_end();

extern Advanced2D::Engine* g_engine;

#endif
