
#include "Advanced2D.h"
#include "Audio.h"
#include <dinput.h>

static Advanced2D::Audio::AudioSample* wobble = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("AUDIO TEST"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(640);
	Advanced2D::Engine::setScreenHeight(480);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	Advanced2D::Engine::showMessage(
	    TEXT("Press mouse button to hear sound clips!"));

	if (!g_engine->getAudio()->load(TEXT("gong.ogg"), TEXT("gong")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load gong.ogg audio"),
		                                     TEXT("game_init"));
		return false;
	}

	if (!g_engine->getAudio()->load(TEXT("explosion.wav"), TEXT("explosion")))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load explosion.wav audio"),
		                                     TEXT("game_init"));
		return false;
	}

	if (NULL == (wobble = g_engine->getAudio()->load(TEXT("wobble.wav"))))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load wobble.wav audio"),
		                                     TEXT("game_init"));
		return false;
	}

	return true;
}

void game_update()
{
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
		case 0:
			g_engine->getAudio()->play(TEXT("gong"));
			break;

		case 1:
			g_engine->getAudio()->play(TEXT("explosion"));
			break;

		case 2:
			g_engine->getAudio()->play(wobble);
			break;
	}
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
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(100, 0, 0));
}

void game_end()
{
	g_engine->getAudio()->stopAll();
	delete wobble;
	wobble = NULL;
}
