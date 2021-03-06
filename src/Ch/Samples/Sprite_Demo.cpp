
#include "Advanced2D.h"
#include "Sprite.h"

#define SCREENW 640
#define SCREENH 480
#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0)

static Advanced2D::Sprite* sprite = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("SPRITE COLOR KEY DEMO"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	sprite = new Advanced2D::Sprite();

	if (!sprite->loadImage(TEXT("fatship_colorkeyed.bmp")))
	{
		Advanced2D::Engine::showFatalMessage(
		    TEXT("Unable to load fatship_colorkeyed.bmp image"),
		    TEXT("game_init"));
		return false;
	}

	return true;
}

void game_update()
{
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
	float cx = static_cast<float>(Advanced2D::Engine::getScreenWidth()) / 2;
	float cy = static_cast<float>(Advanced2D::Engine::getScreenHeight()) / 2;
	float sx = static_cast<float>(sprite->getWidth()) / 2;
	float sy = static_cast<float>(sprite->getHeight()) / 2;
	sprite->setPosition2d(cx - sx, cy - sy);
	sprite->draw();
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
	g_engine->setIdentity();
}

void game_end()
{
	delete sprite;
	sprite = NULL;
}
