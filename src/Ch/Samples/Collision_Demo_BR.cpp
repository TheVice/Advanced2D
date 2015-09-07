
#include "Advanced2D.h"
#include "Texture.h"
#include "Font.h"
#include "Console.h"
#include <stdio.h>
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX_PR 40

static Advanced2D::Texture* asteroid_image = NULL;
static Advanced2D::Texture* collisionBox = NULL;
static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;
static int collisions = 0;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Collision Demo"));
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
	console = new Advanced2D::Console();

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
		_TCHAR szText[32 * sizeof(_TCHAR)];
		Advanced2D::Sprite* asteroid = new Advanced2D::Sprite();
		asteroid->setObjectType(OBJECT_SPRITE);
#if _MSC_VER > 1310
		_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("ASTEROID %i"), n);
#else
		_stprintf(szText, TEXT("ASTEROID %i"), n);
#endif
		asteroid->setName(szText);
		asteroid->setImage(asteroid_image);
		asteroid->setScale(static_cast<float>((rand() % 150 + 50) / 100.0f));
		asteroid->setTotalFrames(64);
		asteroid->setColumns(8);
		asteroid->setSize(60, 60);
		asteroid->setPosition2d(static_cast<float>(rand() % SCREENW),
		                        static_cast<float>(rand() % SCREENH));
		asteroid->setFrameTimer(rand() % 90 + 10);
		asteroid->setCurrentFrame(rand() % 64);

		if (rand() % 2 == 0)
		{
			asteroid->setAnimationDirection(-1);
		}

		asteroid->setVelocity(static_cast<float>((rand() % 10 - 5) / 10.0f),
		                      static_cast<float>((rand() % 10 - 5) / 10.0f));
		asteroid->setCollidable(true);
		asteroid->setMoveTimer(16);
		g_engine->addEntity(asteroid);
	}

	try
	{
		font = new Advanced2D::Font(TEXT("verdana10.dat"));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load verdana10.dat file"),
		                                     TEXT("game_init"));
		return false;
	}

	if (!font->loadImage(TEXT("verdana10.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load verdana10.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	font->setColumns(16);
	font->setSize(20, 16);

	try
	{
		collisionBox = new Advanced2D::Texture(TEXT("highlight.tga"), D3DCOLOR_XRGB(0,
		                                       0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load highlight.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	return true;
}

void updateConsole()
{
	_TCHAR szText[64 * sizeof(_TCHAR)];
	int y = 0;
	console->print(Advanced2D::Engine::getVersionText().c_str(), y++);
	y++;
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("SCREEN : %f ms ( %f fps)"),
	            static_cast<float>(1000.0f / g_engine->getFrameRate_real()),
	            static_cast<float>(g_engine->getFrameRate_real()));
#else
	_stprintf(szText, TEXT("SCREEN : %f ms ( %f fps)"),
	          static_cast<float>(1000.0f / g_engine->getFrameRate_real()),
	          static_cast<float>(g_engine->getFrameRate_real()));
#endif
	console->print(szText, y++);
	y++;
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("CORE : %f ms ( %f fps)"),
	            static_cast<float>(1000.0f / g_engine->getFrameRate_core()),
	            static_cast<float>(g_engine->getFrameRate_core()));
#else
	_stprintf(szText, TEXT("CORE : %f ms ( %f fps)"),
	          static_cast<float>(1000.0f / g_engine->getFrameRate_core()),
	          static_cast<float>(g_engine->getFrameRate_core()));
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Processor throttling: %i"),
	            g_engine->getMaximizeProcessor());
#else
	_stprintf(szText, TEXT("Processor throttling: %i"),
	          g_engine->getMaximizeProcessor());
#endif
	console->print(szText, y++);
	y++;
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Screen: %i"),
	            Advanced2D::Engine::getColorDepth());
#else
	_stprintf(szText, TEXT("Screen: %i"), Advanced2D::Engine::getColorDepth());
#endif
	console->print(szText, y++);
	y++;
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Entities: %i"),
	            static_cast<int>(g_engine->getEntityList()->size()));
#else
	_stprintf(szText, TEXT("Entities: %i"),
	          static_cast<int>(g_engine->getEntityList()->size()));
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Collisions: %i"),
	            collisions);
#else
	_stprintf(szText, TEXT("Collisions: %i"), collisions);
#endif
	console->print(szText, y++);
	y++;
	console->print(TEXT("Press F2 to toggle Processor Throttling"), y);
}

void game_update()
{
	updateConsole();
	collisions = 0;
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

void game_entityRender(Advanced2D::Entity*)
{
}

void game_entityCollision(Advanced2D::Entity* entity1,
                          Advanced2D::Entity* entity2)
{
	if (entity1->getObjectType() != OBJECT_SPRITE ||
	    entity2->getObjectType() != OBJECT_SPRITE)
	{
		return;
	}

	collisions++;
	Advanced2D::Sprite* spr1 = static_cast<Advanced2D::Sprite*>(entity1);
	Advanced2D::Sprite* spr2 = static_cast<Advanced2D::Sprite*>(entity2);
	Advanced2D::Sprite* box = new Advanced2D::Sprite();
	box->setColor(0x33DD4444);
	box->setImage(collisionBox);
	box->setPosition2d(spr1->getPosition());
	box->setScale(spr1->getWidth() * spr1->getScale() / 100.0f);
	box->setLifeTime(100);
	g_engine->addEntity(box);
	box = new Advanced2D::Sprite();
	box->setColor(0x33DD4444);
	box->setImage(collisionBox);
	box->setPosition2d(spr2->getPosition());
	box->setScale(spr2->getWidth() * spr2->getScale() / 100.0f);
	box->setLifeTime(100);
	g_engine->addEntity(box);
}

void game_keyPress(int)
{
}

void game_keyRelease(int aKey)
{
	switch (aKey)
	{
		case DIK_ESCAPE:
			Advanced2D::Engine::shutdown();
			break;

		case DIK_F12:
		case DIK_GRAVE:
			console->setShowing(!console->isShowing());
			break;

		case DIK_F2:
			g_engine->setMaximizeProcessor(!g_engine->getMaximizeProcessor());
			break;
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
	font->print(1, SCREENH - 20, TEXT("Press ~ or F12 to toggle the Console"));

	if (console->isShowing())
	{
		console->draw();
	}
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
	g_engine->setIdentity();
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
	delete console;
	console = NULL;
	delete asteroid_image;
	asteroid_image = NULL;
	delete font;
	font = NULL;
}
