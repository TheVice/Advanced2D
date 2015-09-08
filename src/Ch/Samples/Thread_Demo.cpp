
#include "Advanced2D.h"
#include "Texture.h"
#include "Font.h"
#include "Console.h"
#include "Mathematic.h"
#include "pthread_wrapper.h"
#include <stdio.h>
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define OBJECT_BACKGROUND 1
#define OBJECT_SPRITE 100
#define MAX_PR 50
#define SCALE 70
#define MAXTHREAD 2

static Advanced2D::Texture* circle_image = NULL;
static Advanced2D::Font* font = NULL;
static Advanced2D::Console* console = NULL;
static pthread_t threads[MAXTHREAD];
static bool done = false;
static int thread_counter = 0;
void* thread_function(void* data);
#ifdef _MSC_VER
static pthread_mutex_t mutex;
#else
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
#endif
static int thread_waits = 0;
static int collisions = 0;

void* thread_function(void*)
{
	while (!done)
	{
#ifdef _MSC_VER
		pthread_mutex_lock(&mutex);
#else

		if (pthread_mutex_lock(&mutex) != 0)
		{
			thread_waits++;
		}

#endif
		thread_counter++;
		Advanced2D::Vector3<float> vector1(100.0f, 200.0f, 300.0f);
		Advanced2D::Vector3<float> vector2(400.0f, 500.0f, 600.0f);
		double dist = vector1.distance2d(vector2);
		/*double dist_squared = */pow(dist, 2);
		/*double square_root_of_dist = */sqrt(dist);
		/*double answer = square_root_of_dist;*/
#ifdef _MSC_VER
		pthread_mutex_unlock(&mutex);
#else

		if (pthread_mutex_unlock(&mutex) != 0)
		{
			thread_waits++;
		}

#endif
	}

	pthread_exit(NULL);
	return NULL;
}

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Thread Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
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
		Advanced2D::Sprite* sprite = new Advanced2D::Sprite();
		sprite->setObjectType(OBJECT_SPRITE);
		sprite->setImage(circle_image);
		sprite->setSize(128, 128);
		sprite->setScale((rand() % SCALE + SCALE / 4) / 100.0f);
		sprite->setPosition2d(static_cast<float>(rand() % SCREENW),
		                      static_cast<float>(rand() % SCREENH));
		sprite->setCollisionMethod(Advanced2D::COLLISION_DIST);
		sprite->setVelocity(static_cast<float>(rand() % 30 - 15) / 10.0f,
		                    static_cast<float>(rand() % 30 - 15) / 10.0f);
		g_engine->addEntity(sprite);
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
#ifdef _MSC_VER
	pthread_mutex_init(&mutex, NULL);
#endif

	for (int n = 0; n < MAXTHREAD; ++n)
	{
		int mythread_id = n;
		pthread_create(&threads[n], NULL, thread_function,
		               reinterpret_cast<void*>(&mythread_id));
	}

	return true;
}

void updateConsole()
{
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
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("THREAD COUTER : %i"), thread_counter);
#else
	_stprintf(szText, TEXT("THREAD COUTER : %i"),
	          thread_counter);
#endif
	console->print(szText, y++);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("THREAD WAITS : %i"),
	            thread_waits);
#else
	_stprintf(szText, TEXT("THREAD WAITS : %i"), thread_waits);
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
	pthread_mutex_lock(&mutex);
	updateConsole();
	collisions = 0;
	pthread_mutex_unlock(&mutex);
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

void game_entityCollision(Advanced2D::Entity* aEntity1,
                          Advanced2D::Entity* aEntity2)
{
	if (aEntity1->getObjectType() != OBJECT_SPRITE ||
	    aEntity2->getObjectType() != OBJECT_SPRITE)
	{
		return;
	}

	collisions++;
	Advanced2D::Sprite* a = static_cast<Advanced2D::Sprite*>(aEntity1);
	Advanced2D::Sprite* b = static_cast<Advanced2D::Sprite*>(aEntity2);
	float x1 = a->getPosition().mX;
	float y1 = a->getPosition().mY;
	float x2 = b->getPosition().mX;
	float y2 = b->getPosition().mY;
	float vx1 = a->getVelocity().mX;
	float vy1 = a->getVelocity().mY;
	float vx2 = b->getVelocity().mX;
	float vy2 = b->getVelocity().mY;

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

	a->setVelocity(vx1, vy1);
	b->setVelocity(vx2, vy2);
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

	for (std::list<Advanced2D::Entity*>::iterator iter = MyList.begin();
	     iter != MyList.end();
	     ++iter)
	{
		delete (*iter);
	}

	MyList.clear();
	done = true;

	for (int n = 0; n < MAXTHREAD; ++n)
	{
		void* ret = NULL;
		pthread_join(threads[n], &ret);
	}

	pthread_mutex_destroy(&mutex);
	delete font;
	font = NULL;
	delete console;
	console = NULL;
	delete circle_image;
	circle_image = NULL;
}
