
#include "Advanced2D.h"
#include "Sprite.h"

Advanced2D::Sprite* sprite = NULL;

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000)?1:0)

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("SPRITE ROTATION AND SCALING DEMO"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(800);
	Advanced2D::Engine::setScreenHeight(600);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	sprite = new Advanced2D::Sprite();

	if (!sprite->loadImage(TEXT("fatship.tga")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load fatship.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	return true;
}

void game_update()
{
	static float scale = 0.01f;
	sprite->setPosition2D(400, 300);
	sprite->setRotation(Advanced2D::Timer::getTimer() / 600.0f);
	float s = sprite->getScale() + scale;

	if (s < 0.01f || s > 2.5f)
	{
		scale *= -1;
	}

	sprite->setScale(s);

	if (KEY_DOWN(VK_ESCAPE))
	{
		Advanced2D::Engine::shutdown();
	}
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
	sprite->draw();
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void game_end()
{
	delete sprite;
	sprite = NULL;
}
