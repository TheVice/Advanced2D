
#include "Advanced2D.h"

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Ch1_HelloAdvanced2D"));
	g_engine->showMessage(Advanced2D::Engine::getVersionText().c_str(),
	                      TEXT("TEXT ENGINE"));
	return true;
}

bool game_init()
{
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
}

void game_render3d()
{
}

void game_end()
{
}
