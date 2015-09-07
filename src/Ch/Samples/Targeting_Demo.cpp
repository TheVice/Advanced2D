
#include "Advanced2D.h"
#include "Texture.h"
#include "Font.h"
#include "Console.h"
#include "Mathematic.h"
#include "Audio.h"
#include <stdio.h>
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define BULLET_VEL 3
#define ASTEROID_VEL 3

#define OBJECT_BACKGROUND 1
#define OBJECT_SHIP 10
#define OBJECT_BULLET 20
#define OBJECT_ASTEROID 30
#define OBJECT_EXPLOSION 40

static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;
static Advanced2D::Texture* bullet_image = NULL;
static Advanced2D::Texture* asteroid_image = NULL;
static Advanced2D::Texture* explosion_image = NULL;
static Advanced2D::Vector3<float> ship_position, nearest_asteroid, target_lead;
static Advanced2D::Timer fireTimer;
static float ship_angle = 90.0f, nearest_distance = 0.0f;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Targeting Demo"));
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
	g_engine->addEntity(background);
	console = new Advanced2D::Console();
	Advanced2D::Sprite* ship = new Advanced2D::Sprite();

	if (!ship->loadImage(TEXT("spaceship80.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load spaceship80.tga image"),
		    TEXT("game_init"));
		return false;
	}

	ship->setObjectType(OBJECT_SHIP);
	ship->setRotation(Advanced2D::Mathematic<float>::toRadians(90));
	ship->setPosition2d(10.0, SCREENH / 2 - 32);
	g_engine->addEntity(ship);

	try
	{
		bullet_image = new Advanced2D::Texture(TEXT("plasma.tga"), D3DCOLOR_XRGB(0, 0,
		                                       0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load plasma.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

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

	try
	{
		explosion_image = new Advanced2D::Texture(TEXT("explosion_30_128.tga"),
		        D3DCOLOR_XRGB(0, 0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load explosion_30_128.tga image"),
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

	if (!g_engine->getAudio()->load(TEXT("fire.wav"), TEXT("fire")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load fire.wav audio"),
		                                     TEXT("game_init"));
		return false;
	}

	if (!g_engine->getAudio()->load(TEXT("boom.wav"), TEXT("boom")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load boom.wav audio"),
		                                     TEXT("game_init"));
		return false;
	}

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
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Nearest asteroid: %f %f"),
	            static_cast<float>(nearest_asteroid.mX),
	            static_cast<float>(nearest_asteroid.mY));
#else
	_stprintf(szText, TEXT("Nearest asteroid: %f %f"),
	          static_cast<float>(nearest_asteroid.mX),
	          static_cast<float>(nearest_asteroid.mY));
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Nearest distance: %f"), nearest_distance);
#else
	_stprintf(szText, TEXT("Nearest distance: %f"), nearest_distance);
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Leading target: %f %f"),
	            static_cast<float>(target_lead.mX), static_cast<float>(target_lead.mY));
#else
	_stprintf(szText, TEXT("Leading target: %f %f"),
	          static_cast<float>(target_lead.mX), static_cast<float>(target_lead.mY));
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Angle to target: %f"), ship_angle);
#else
	_stprintf(szText, TEXT("Angle to target: %f"), ship_angle);
#endif
	console->print(szText, y);
}

void game_update()
{
	updateConsole();
}

void firebullet()
{
	Advanced2D::Sprite* ship = static_cast<Advanced2D::Sprite*>
	                           (g_engine->findEntity(OBJECT_SHIP));

	if (!ship)
	{
		Advanced2D::Engine::shutdown();
	}

	Advanced2D::Sprite* bullet = new Advanced2D::Sprite();
	bullet->setObjectType(OBJECT_BULLET);
	bullet->setImage(bullet_image);
	bullet->setMoveTimer(1);
	bullet->setLifeTime(5000);
	float angle = static_cast<float>(Advanced2D::Mathematic<float>::toRadians(
	                                     ship_angle));
	bullet->setRotation(angle);
	bullet->setPosition2d(ship->getPosition().mX + ship->getWidth() / 2,
	                      ship->getPosition().mY + ship->getHeight() / 2 - 8);
	bullet->setVelocity(Advanced2D::Mathematic<float>::linearVelocityX(
	                        ship_angle) * BULLET_VEL,
	                    Advanced2D::Mathematic<float>::linearVelocityY(ship_angle) * BULLET_VEL);
	g_engine->addEntity(bullet);
	g_engine->getAudio()->play(TEXT("fire"));
}

void targetNearestAsteroid(Advanced2D::Sprite* asteroid)
{
	Advanced2D::Vector3<float> target = asteroid->getPosition();
	float dist = static_cast<float>(ship_position.distance2d(target));

	if (dist < nearest_distance)
	{
		nearest_asteroid = target;
		nearest_distance = dist;
		target_lead.mX = (asteroid->getVelocity().mX * 0.01f);
		target_lead.mY = (asteroid->getVelocity().mY * 0.01f);
		nearest_asteroid.mX = (nearest_asteroid.mX + target_lead.mX);
		nearest_asteroid.mY = (nearest_asteroid.mY + target_lead.mY);
		ship_angle = (90 + Advanced2D::Mathematic<float>::toDegrees(
		                  Advanced2D::Mathematic<float>::angleToTarget(ship_position, nearest_asteroid)));
	}

	if ((nearest_distance < 1200.0f) && fireTimer.stopwatch(100))
	{
		firebullet();
	}
}

void game_entityUpdate(Advanced2D::Entity* entity)
{
	Advanced2D::Vector3<float> position;
	Advanced2D::Sprite* ship, *bullet, *asteroid;

	switch (entity->getObjectType())
	{
		case OBJECT_SHIP:
			ship = static_cast<Advanced2D::Sprite*>(entity);
			ship_position = ship->getPosition();
			ship->setRotation(Advanced2D::Mathematic<float>::toRadians(ship_angle));
			break;

		case OBJECT_BULLET:
			bullet = static_cast<Advanced2D::Sprite*>(entity);

			if (bullet->getPosition().mX > SCREENW)
			{
				bullet->setAlive(false);
			}

			break;

		case OBJECT_ASTEROID:
			asteroid = static_cast<Advanced2D::Sprite*>(entity);

			if (asteroid->getPosition().mX < -64)
			{
				asteroid->getPosition().mX = SCREENW;
			}

			targetNearestAsteroid(asteroid);
			break;

		default:
			return;
	}
}

void game_entityRender(Advanced2D::Entity*)
{
}

void game_entityCollision(Advanced2D::Entity* entity1,
                          Advanced2D::Entity* entity2)
{
	Advanced2D::Sprite* asteroid, *bullet, *expl;

	if ((entity1->getObjectType() == OBJECT_ASTEROID) &&
	    (entity2->getObjectType() == OBJECT_BULLET))
	{
		asteroid = static_cast<Advanced2D::Sprite*>(entity1);
		bullet = static_cast<Advanced2D::Sprite*>(entity2);
	}
	else if ((entity1->getObjectType() == OBJECT_BULLET) &&
	         (entity2->getObjectType() == OBJECT_ASTEROID))
	{
		asteroid = static_cast<Advanced2D::Sprite*>(entity2);
		bullet = static_cast<Advanced2D::Sprite*>(entity1);
	}
	else
	{
		return;
	}

	try
	{
		expl = new Advanced2D::Sprite();
	}
	catch (const std::exception&)
	{
		return;
	}

	expl->setObjectType(OBJECT_EXPLOSION);
	expl->setImage(explosion_image);
	expl->setColumns(6);
	expl->setCollidable(false);
	expl->setSize(128, 128);
	expl->setPosition2d(asteroid->getPosition().mX - 32,
	                    asteroid->getPosition().mY - 32);
	expl->setTotalFrames(30);
	expl->setFrameTimer(40);
	expl->setLifeTime(1000);
	g_engine->addEntity(expl);
	bullet->setAlive(false);
	asteroid->setAlive(false);
	g_engine->getAudio()->play(TEXT("boom"));
}

void addAsteroid()
{
	Advanced2D::Sprite* asteroid = new Advanced2D::Sprite();
	asteroid->setObjectType(OBJECT_ASTEROID);
	asteroid->setVelocity(-ASTEROID_VEL, 0.0);
	asteroid->setPosition2d(static_cast<float>(SCREENW),
	                        static_cast<float>(50 + rand() % (SCREENH - 150)));
	asteroid->setImage(asteroid_image);
	asteroid->setTotalFrames(64);
	asteroid->setColumns(8);
	asteroid->setSize(60, 60);
	asteroid->setFrameTimer(rand() % 100);
	asteroid->setCurrentFrame(rand() % 64);

	if (rand() % 2 == 0)
	{
		asteroid->setAnimationDirection(-1);
	}

	g_engine->addEntity(asteroid);
}

void game_keyPress(int aKey)
{
	switch (aKey)
	{
		case DIK_SPACE:
			addAsteroid();
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
	font->print(1, SCREENH - 40, TEXT("Press SPACE to launch an asteroid"));

	if (console->isShowing())
	{
		console->draw();
	}

	nearest_distance = 999999;
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
		if ((*iter))
		{
			delete (*iter);
		}

		(*iter) = NULL;
	}

	MyList.clear();
	delete font;
	font = NULL;
	delete console;
	console = NULL;
	delete bullet_image;
	bullet_image = NULL;
	delete asteroid_image;
	asteroid_image = NULL;
	delete explosion_image;
	explosion_image = NULL;
}
