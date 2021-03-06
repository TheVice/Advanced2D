
#include "Advanced2D.h"
#include "Sprite.h"
#include "ParticleEmitter.h"
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0)

static Advanced2D::ParticleEmitter* p = NULL;
static Advanced2D::Sprite* cursor = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("INPUT DEMO"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	//g_engine->setMaximizeProcessor(true);
	p = new Advanced2D::ParticleEmitter();

	if (!p->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	p->setPosition2d(100.0f, 300.0f);
	p->setDirection(0.0f);
	p->setMax(0);
	p->setAlphaRange(50, 200);
	p->setSpread(270);
	p->setScale(1.5f);
	p->setLength(2000.0f);
	cursor = new Advanced2D::Sprite();

	if (!cursor->loadImage(TEXT("particle16.tga")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load particle16.tga image"),
		    TEXT("game_init"));
		return false;
	}

	return true;
}

void game_update()
{
	//move particles
	p->update();
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

void game_keyRelease(int aKey)
{
	if (DIK_ESCAPE == aKey)
	{
		Advanced2D::Engine::shutdown();
	}
}

void game_mouseButton(int aButton)
{
	switch (aButton)
	{
		case 0://button 1
			p->setVelocity((rand() % 10 - 5) / 500.0f);
			p->add();
			break;
	}
}

void game_mouseMotion(int, int)
{
}

void game_mouseMove(int aX, int aY)
{
	float fx = static_cast<float>(aX);
	float fy = static_cast<float>(aY);
	cursor->setPosition2d(fx, fy);
	p->setPosition2d(fx, fy);
}

void game_mouseWheel(int)
{
}

void game_render2d()
{
	p->draw();
	cursor->draw();
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 0));
}

void game_end()
{
	delete p;
	p = NULL;
	delete cursor;
	cursor = NULL;
}
