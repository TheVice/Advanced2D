
#include "Advanced2D.h"
#include "Texture.h"
#include "Font.h"
#include "Console.h"
#include "Mathematic.h"
#include <stdio.h>
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define VELOCITY_D 0.0001
#define ROCKETVEL 3
#define OBJECT_SHIP 100
#define OBJECT_ROCKET 200

static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;
static Advanced2D::Sprite* ship_g = NULL;
static Advanced2D::Vector3<float> velocity;
static Advanced2D::Texture* rocket_image = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Velocity Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	console = new Advanced2D::Console();
	ship_g = new Advanced2D::Sprite();

	if (!ship_g->loadImage(TEXT("fatship256.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load fatship256.tga image"),
		    TEXT("game_init"));
		return false;
	}

	ship_g->setObjectType(OBJECT_SHIP);
	ship_g->setRotation(Advanced2D::Mathematic<float>::toRadians(90));
	ship_g->setPosition2d(10.0f,
	                      static_cast<float>(SCREENH - ship_g->getHeight()) / 2);
	g_engine->addEntity(ship_g);

	try
	{
		rocket_image = new Advanced2D::Texture(TEXT("fatrocket64.tga"), D3DCOLOR_XRGB(0,
		                                       0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load fatrocket64.tga image"),
		    TEXT("game_init"));
		return false;
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
	//g_engine->setMaximizeProcessor(!g_engine->getMaximizeProcessor());
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
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Entities: %i"),
	            static_cast<int>(g_engine->getEntityList()->size()));
#else
	_stprintf(szText, TEXT("Entities: %i"),
	          static_cast<int>(g_engine->getEntityList()->size()));
#endif
	console->print(szText, y);
}

void game_update()
{
	updateConsole();
}

void game_entityUpdate(Advanced2D::Entity* aEntity)
{
	switch (aEntity->getObjectType())
	{
		case OBJECT_SHIP:
		{
			Advanced2D::Sprite* ship = static_cast<Advanced2D::Sprite*>(aEntity);
			Advanced2D::Vector3<float> position = ship->getPosition();
			float y = static_cast<float>(position.mY + velocity.mY);

			if (y < 0.0f)
			{
				y = 0.0f;
				velocity.mY = 0;
			}

			if (y > SCREENH - 128)
			{
				y = SCREENH - 128;
				velocity.mY = 0;
			}

			position.mY = y;
			ship->setPosition2d(position);
		}
		break;

		case OBJECT_ROCKET:
		{
			Advanced2D::Sprite* rocket = static_cast<Advanced2D::Sprite*>(aEntity);

			if (rocket->getPosition().mX > SCREENW)
			{
				rocket->setAlive(false);
			}
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

void firerocket()
{
	Advanced2D::Sprite* ship = static_cast<Advanced2D::Sprite*>
	                           (g_engine->findEntity(OBJECT_SHIP));

	if (!ship)
	{
		Advanced2D::Engine::shutdown();
	}

	Advanced2D::Sprite* rocket = new Advanced2D::Sprite();
	rocket->setObjectType(OBJECT_ROCKET);
	rocket->setImage(rocket_image);
	rocket->setMoveTimer(1);
	rocket->setCollidable(false);
	float angel = static_cast<float>(90 + rand () % 40 - 20);
	rocket->setRotation(Advanced2D::Mathematic<float>::toRadians(angel));
	float x = ship->getPosition().mX + ship->getWidth();
	float y = ship->getPosition().mY + static_cast<float>(ship->getHeight() -
	          rocket->getHeight()) / 2;
	rocket->setPosition2d(x, y);
	rocket->setVelocity(Advanced2D::Mathematic<float>::linearVelocityX(
	                        angel) * ROCKETVEL,
	                    Advanced2D::Mathematic<float>::linearVelocityY(angel) * ROCKETVEL);
	g_engine->addEntity(rocket);
}

void game_keyPress(int aKey)
{
	float y;

	switch (aKey)
	{
		case DIK_UP:
		case DIK_W:
			y = static_cast<float>(velocity.mY - VELOCITY_D);

			if (y < -3.0)
			{
				y = -3.0;
			}

			velocity.mY = y;
			break;

		case DIK_DOWN:
		case DIK_S:
			y = static_cast<float>(velocity.mY + VELOCITY_D);

			if (y > 3.0)
			{
				y = 3.0;
			}

			velocity.mY = y;
			break;

		case DIK_SPACE:
		case DIK_LCONTROL:
			firerocket();
			break;
	}
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
	font->print(1, SCREENH - 40, TEXT("Press SPACE to fire"));

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

	for (std::list<Advanced2D::Entity*>::iterator iter = MyList.begin();
	     iter != MyList.end();
	     ++iter)
	{
		delete (*iter);
	}

	MyList.clear();
	delete font;
	font = NULL;
	delete console;
	console = NULL;
	delete rocket_image;
	rocket_image = NULL;
}
