
#include "Advanced2D.h"
#include "Texture.h"
#include "Font.h"
#include <stdio.h>
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX_PR 50

static Advanced2D::Sprite* panel = NULL;
static Advanced2D::Texture* asteroid_image = NULL;
static Advanced2D::Font* system12 = NULL;
static Advanced2D::Font* nonprop = NULL;
static Advanced2D::Font* verdana10 = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Font Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	Advanced2D::Sprite* background = new Advanced2D::Sprite();

	if (!background->loadImage(TEXT("orion.bmp")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load orion.bmp image"),
		                                     TEXT("game_init"));
		return false;
	}

	background->setObjectType(OBJECT_BACKGROUND);
	g_engine->addEntity(background);

	try
	{
		asteroid_image = new Advanced2D::Texture(TEXT("asteroid.tga"), D3DCOLOR_XRGB(0,
		        0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load asteroid.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	for (int n = 0; n < MAX_PR; ++n)
	{
		Advanced2D::Sprite* asteroid = new Advanced2D::Sprite();
		asteroid->setObjectType(OBJECT_SPRITE);
		asteroid->setImage(asteroid_image);
		asteroid->setTotalFrames(64);
		asteroid->setColumns(8);
		asteroid->setSize(60, 60);
		asteroid->setPosition2D(static_cast<float>(rand() % SCREENW),
		                        static_cast<float>(rand() % SCREENH));
		asteroid->setFrameTimer(rand() % 100);
		asteroid->setCurrentFrame(rand() % 64);

		if (rand() % 2 == 0)
		{
			asteroid->setAnimationDirection(-1);
		}

		asteroid->setVelocity(static_cast<float>((rand() % 10) / 10.0f),
		                      static_cast<float>((rand() % 10) / 10.0f));
		g_engine->addEntity(asteroid);
	}

	panel = new Advanced2D::Sprite();

	if (!panel->loadImage(TEXT("panel.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load panel.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	panel->setScale(SCREENW / 640.0f);
	panel->setColor(0xBBFFFFFF);

	try
	{
		system12 = new Advanced2D::Font(TEXT("system12.dat"));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load system12.dat file"),
		                                     TEXT("game_init"));
		return false;
	}

	if (!system12->loadImage(TEXT("system12.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load system12.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	system12->setColumns(16);
	system12->setSize(14, 16);
	nonprop = new Advanced2D::Font();

	if (!nonprop->loadImage(TEXT("system12.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load system12.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	nonprop->setColumns(16);
	nonprop->setSize(14, 16);

	try
	{
		verdana10 = new Advanced2D::Font(TEXT("verdana10.dat"));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load verdana10.dat file"),
		                                     TEXT("game_init"));
		return false;
	}

	if (!verdana10->loadImage(TEXT("verdana10.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load verdana10.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	verdana10->setColumns(16);
	verdana10->setSize(20, 16);
	return true;
}

void game_update()
{
}

void game_entityUpdate(Advanced2D::Entity* entity)
{
	if (entity->getObjectType() != OBJECT_SPRITE)
	{
		return;
	}

	Advanced2D::Sprite* spr = static_cast<Advanced2D::Sprite*>(entity);

	if (spr->getPosition().mX < 60.0f)
	{
		spr->getPosition().mX = SCREENW;
	}

	if (spr->getPosition().mX > SCREENW)
	{
		spr->getPosition().mX = -60;
	}

	if (spr->getPosition().mY < -60.0f)
	{
		spr->getPosition().mY = SCREENH;
	}

	if (spr->getPosition().mY > SCREENH)
	{
		spr->getPosition().mY = -60;
	}
}

void game_entityRender(class Advanced2D::Entity*)
{
}

void game_keyPress(int)
{
}

void game_keyRelease(int aKey)
{
	if (DIK_ESCAPE == aKey)
	{
		Advanced2D::Engine::shutdown();
	}
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
	panel->draw();
	nonprop->print(1, 1, TEXT("This is the SYSTEM 12 font WITHOUT proportion data"),
	               0xFF111111);
	nonprop->print(1, 20, TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"), 0xFF111111);
	nonprop->print(1, 40,
	               TEXT("abcdefghijklmnopqrstuvwxyz~`!@#$%^&*()-_=+[{]};:'\",<.>/\\?"),
	               0xFF111111);
	system12->setScale(1.0f);
	system12->print(1, 80, TEXT("This is the SYSTEM 12 font WITH proportion data"),
	                0xFF111111);
	system12->print(1, 100, TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"),
	                0xFF111111);
	system12->print(1, 120,
	                TEXT("abcdefghijklmnopqrstuvwxyz~`!@#$%^&*()-_=+[{]};:'\",<.>/\\?"),
	                0xFF111111);
	_TCHAR szText[64 * sizeof(_TCHAR)];

	for (float f = 0.5f; f < 2.0f; f += 0.25f)
	{
		verdana10->setScale(f);
#if _MSC_VER > 1310
		_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
		            TEXT("VERDANA 10 font scaled at %f"), f * 100);
#else
		_stprintf(szText, TEXT("VERDANA 10 font scaled at %f"), f * 100);
#endif
		verdana10->print(f * 20, 100 + f * 120, szText, 0xFF111111);
	}

	verdana10->setScale(1.5f);
	verdana10->print(600, 140, g_engine->getVersionText().c_str(), 0xFF991111);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("SCREEN: %f ms"),
	            1000.0f / g_engine->getFrameRate_real());
#else
	_stprintf(szText, TEXT("SCREEN: %f ms"),
	          1000.0f / g_engine->getFrameRate_real());
#endif
	verdana10->print(600, 180, szText, 0xFF119911);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("CORE: %f ms"),
	            1000.0f / g_engine->getFrameRate_core());
#else
	_stprintf(szText, TEXT("CORE: %f ms"), 1000.0f / g_engine->getFrameRate_core());
#endif
	verdana10->print(600, 220, szText, 0xFF111199);
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void game_end()
{
	std::list<Advanced2D::Entity*> MyList = (*g_engine->getEntityList());
	std::list<Advanced2D::Entity*>::iterator iter;

	for (iter = MyList.begin(); iter != MyList.end(); ++iter)
	{
		delete (*iter);
	}

	MyList.clear();
	delete panel;
	panel = NULL;
	delete asteroid_image;
	asteroid_image = NULL;
	delete system12;
	system12 = NULL;
	delete nonprop;
	nonprop = NULL;
	delete verdana10;
	verdana10 = NULL;
}
