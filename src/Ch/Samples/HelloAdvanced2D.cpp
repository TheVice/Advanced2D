
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

void game_render3d()
{
}

void game_render2d()
{
}

void game_end()
{
}
