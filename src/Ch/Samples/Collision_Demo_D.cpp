
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
#define SCALE 70

static Advanced2D::Texture* ball_image = NULL;
static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;
static int collisions = 0;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Collision Demo (DISTANCE)"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	Advanced2D::Sprite* background = new Advanced2D::Sprite();

	if (!background->loadImage(TEXT("craters.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load craters.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	background->setObjectType(OBJECT_BACKGROUND);
	background->setCollidable(false);
	g_engine->addEntity(background);
	console = new Advanced2D::Console();

	try
	{
		ball_image = new Advanced2D::Texture(TEXT("lightningball.tga"), D3DCOLOR_XRGB(0,
		                                     0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load lightningball.tga image"),
		    TEXT("game_init"));
		return false;
	}

	for (int n = 0; n < MAX_PR; ++n)
	{
		Advanced2D::Sprite* sprite = new Advanced2D::Sprite();
		sprite->setObjectType(OBJECT_SPRITE);
		sprite->setImage(ball_image);
		sprite->setSize(128, 128);
		sprite->setScale(static_cast<float>((rand() % SCALE + SCALE / 4) / 100.0f));
		sprite->setPosition2d(static_cast<float>(rand() % SCREENW),
		                      static_cast<float>(rand() % SCREENH));
		sprite->setCollisionMethod(Advanced2D::COLLISION_DIST);
		sprite->setVelocity(static_cast<float>((rand() % 30 - 15) / 10.0f),
		                    static_cast<float>((rand() % 30 - 15) / 10.0f));
		g_engine->addEntity(sprite);
	}

	try
	{
		font = new Advanced2D::Font(TEXT("verdana10.dat"));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load verdana10.dat image"),
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
	            g_engine->getColorDepth());
#else
	_stprintf(szText, TEXT("Screen: %i"), g_engine->getColorDepth());
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
	float w = static_cast<float>(spr->getWidth() * spr->getScale());
	float h = static_cast<float>(spr->getHeight() * spr->getScale());
	float vx = static_cast<float>(spr->getVelocity().mX);
	float vy = static_cast<float>(spr->getVelocity().mY);

	if (spr->getPosition().mX < 0.0f)
	{
		spr->getPosition().mX = 0.0f;
		vx = fabs(vx);
	}
	else if (spr->getPosition().mX > SCREENW - w)
	{
		spr->getPosition().mX = SCREENW - w;
		vx = fabs(vx) * (-1);
	}

	if (spr->getPosition().mY < 0.0f)
	{
		spr->getPosition().mY = 0.0f;
		vy = fabs(vy);
	}

	if (spr->getPosition().mY > SCREENH - h)
	{
		spr->getPosition().mY = SCREENH - w;
		vy = fabs(vy) * (-1);
	}

	spr->setVelocity(vx, vy);
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

	Advanced2D::Sprite* spr1 = static_cast<Advanced2D::Sprite*>(entity1);
	Advanced2D::Sprite* spr2 = static_cast<Advanced2D::Sprite*>(entity2);
	collisions++;
	float x1 = spr1->getPosition().mX;
	float y1 = spr1->getPosition().mY;
	float x2 = spr2->getPosition().mX;
	float y2 = spr2->getPosition().mY;
	float vx1 = spr1->getVelocity().mX;
	float vy1 = spr1->getVelocity().mY;
	float vx2 = spr2->getVelocity().mX;
	float vy2 = spr2->getVelocity().mY;

	if (x1 < x2)
	{
		vx1 = fabs(vx1) * (-1);
		vx2 = fabs(vx2);
	}
	else if (x1 > x2)
	{
		vx1 = fabs(vx1);
		vx2 = fabs(vx2) * (-1);
	}

	if (y1 < y2)
	{
		vy1 = fabs(vy1) * (-1);
		vy2 = fabs(vy2);
	}
	else if (y1 > y2)
	{
		vy1 = fabs(vy1);
		vy2 = fabs(vy2) * (-1);
	}

	spr1->setVelocity(vx1, vy1);
	spr2->setVelocity(vx2, vy2);
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
	delete ball_image;
	ball_image = NULL;
	delete font;
	font = NULL;
}
