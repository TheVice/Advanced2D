
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
#define MAX_PR 5000
#define SCALE 20

static Advanced2D::Texture* circle_image = NULL;
static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Engine Thread Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

void add_sprite()
{
	Advanced2D::Sprite* sprite = new Advanced2D::Sprite();
	sprite->setObjectType(OBJECT_SPRITE);
	sprite->setImage(circle_image);
	D3DCOLOR color = D3DCOLOR_RGBA(0, rand() % 255, rand() % 255, rand() % 100);
	sprite->setColor(color);
	sprite->setSize(128, 128);
	sprite->setScale((rand() % SCALE + SCALE / 4) / 100.0f);
	sprite->setPosition2d(static_cast<float>(rand() % SCREENW),
	                      static_cast<float>(rand() % SCREENH));
	sprite->setCollidable(false);
	sprite->setLifeTime(rand() % 30000);
	sprite->setVelocity(static_cast<float>(rand() % 30 - 15) / 10.0f,
	                    static_cast<float>(rand() % 30 - 15) / 10.0f);
	g_engine->addEntity(sprite);
}

bool game_init()
{
	Advanced2D::Sprite* background = new Advanced2D::Sprite();

	if (!background->loadImage(TEXT("galaxies.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load galaxies.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	background->setObjectType(OBJECT_BACKGROUND);
	background->setCollidable(false);
	g_engine->addEntity(background);
	console = new Advanced2D::Console();
	console->setShowing(true);

	try
	{
		circle_image = new Advanced2D::Texture(TEXT("circle.tga"), D3DCOLOR_XRGB(0, 0,
		                                       0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load circle.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	for (int n = 0; n < MAX_PR; ++n)
	{
		add_sprite();
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
	g_engine->setMaximizeProcessor(true);
	return true;
}

void updateConsole()
{
	static Advanced2D::Timer timer;

	if (!timer.stopwatch(50))
	{
		return;
	}

	_TCHAR szText[64 * sizeof(_TCHAR)];
	int y = 0;
	console->print(Advanced2D::Engine::getVersionText().c_str(), y++);
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
	console->print(TEXT("Press F2 to toggle Processor Throttling"), y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Entities : %i"),
	            static_cast<int>(g_engine->getEntityList()->size()));
#else
	_stprintf(szText, TEXT("Entities : %i"),
	          static_cast<int>(g_engine->getEntityList()->size()));
#endif
	console->print(szText, y);
}

void game_update()
{
	add_sprite();
	updateConsole();
}

void game_entityUpdate(Advanced2D::Entity* aEntity)
{
	switch (aEntity->getObjectType())
	{
		case OBJECT_SPRITE:
		{
			Advanced2D::Sprite* spr = static_cast<Advanced2D::Sprite*>(aEntity);
			float w = static_cast<float>(spr->getWidth()) * spr->getScale();
			float h = static_cast<float>(spr->getHeight()) * spr->getScale();
			float vx = spr->getVelocity().mX;
			float vy = spr->getVelocity().mY;

			if (spr->getPosition().mX < 0)
			{
				spr->getPosition().mX = 0;
				vx = fabs(vx);
			}
			else if (spr->getPosition().mX > SCREENW - w)
			{
				spr->getPosition().mX = (SCREENW - w);
				vx = fabs(vx) * (-1);
			}

			if (spr->getPosition().mY < 0)
			{
				spr->getPosition().mY = 0;
				vy = fabs(vy);
			}
			else if (spr->getPosition().mY > SCREENH - h)
			{
				spr->getPosition().mY = (SCREENH - h);
				vy = fabs(vy) * (-1);
			}

			spr->setVelocity(vx, vy);
		}
		break;

		default:
			return;
	}
}

void game_entityRender(Advanced2D::Entity*)
{
}

void game_entityCollision(Advanced2D::Entity*, Advanced2D::Entity*)
{
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
	delete font;
	font = NULL;
	delete console;
	console = NULL;
	delete circle_image;
	circle_image = NULL;
}
