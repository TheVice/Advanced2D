
#include "Advanced2D.h"
#include "Sprite.h"
#include "ParticleEmitter.h"

static Advanced2D::ParticleEmitter* pa = NULL;
static Advanced2D::ParticleEmitter* pb = NULL;
static Advanced2D::ParticleEmitter* pc = NULL;
static Advanced2D::ParticleEmitter* pd = NULL;
static Advanced2D::ParticleEmitter* pe = NULL;

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0)

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("PARTICLE DEMO"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(1024);
	Advanced2D::Engine::setScreenHeight(768);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	g_engine->setMaximizeProcessor(true);
	pa = new Advanced2D::ParticleEmitter();

	if (!pa->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	pa->setPosition2d(100.0f, 300.0f);
	pa->setDirection(0.0f);
	pa->setMax(500);
	pa->setAlphaRange(100, 255);
	pa->setSpread(30);
	pa->setVelocity(2.0f);
	pa->setLength(250.0f);
	pb = new Advanced2D::ParticleEmitter();

	if (!pb->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	pb->setPosition2d(300.0f, 100.0f);
	pb->setDirection(180.0f);
	pb->setScale(0.6f);
	pb->setMax(500);
	pb->setAlphaRange(0, 100);
	pb->setColorRange(200, 0, 0, 255, 10, 10);
	pb->setSpread(40);
	pb->setVelocity(2.0f);
	pb->setLength(200.0f);
	pc = new Advanced2D::ParticleEmitter();

	if (!pc->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	pc->setPosition2d(250.0f, 525.0f);
	pc->setDirection(0.0f);
	pc->setScale(0.5f);
	pc->setMax(2000);
	pc->setAlphaRange(100, 150);
	pc->setColorRange(0, 0, 200, 10, 10, 255);
	pc->setSpread(5);
	pc->setVelocity(0.2f);
	pc->setLength(180.0f);
	pd = new Advanced2D::ParticleEmitter();

	if (!pd->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	pd->setPosition2d(750.0f, 650.0f);
	pd->setDirection(0.0f);
	pd->setScale(0.75f);
	pd->setMax(10);
	pd->setAlphaRange(50, 100);
	pd->setColorRange(210, 50, 0, 255, 255, 1);
	pd->setSpread(40);
	pd->setVelocity(2.0f);
	pd->setLength(100.0f);
	pe = new Advanced2D::ParticleEmitter();

	if (!pe->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	pe->setPosition2d(730.0f, 575.0f);
	pe->setDirection(0.0f);
	pe->setScale(4.0f);
	pe->setMax(1000);
	pe->setAlphaRange(1, 20);
	pe->setColorRange(250, 250, 250, 255, 255, 255);
	pe->setSpread(80);
	pe->setVelocity(2.0f);
	pe->setLength(800.0f);
	return true;
}

void game_update()
{
	//move particles
	pa->update();
	pb->update();
	//update the circular emitter
	pc->setDirection(pc->getDirection() + 0.2f);
	pc->update();
	//update the rotating emitter
	static const float unit = static_cast<float>(M_PI / 36000.0f);
	static const float radius = 150.0f;
	static float angle = 0.0f;
	angle += unit;

	if (angle > 360)
	{
		angle = 360 - angle;
	}

	float x = 750 + cos(angle) * radius;
	float y = 500 + sin(angle) * radius;
	pd->setPosition2d(x, y);
	pd->update();
	//update smoke emitter
	pe->setPosition2d(x, y);
	pe->update();

	if (KEY_DOWN(VK_ESCAPE))
	{
		Advanced2D::Engine::shutdown();
	}
}

void game_entityUpdate(Advanced2D::Entity*)
{
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

void game_keyRelease(int)
{
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
	pa->draw();
	pb->draw();
	pc->draw();
	pd->draw();
	pe->draw();
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(255, 255, 255));
}

void game_end()
{
	delete pa;
	pa = NULL;
	delete pb;
	pb = NULL;
	delete pc;
	pc = NULL;
	delete pd;
	pd = NULL;
	delete pe;
	pe = NULL;
}
