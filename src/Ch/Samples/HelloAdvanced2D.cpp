
#include "Advanced2D.h"

bool game_preload()
{
	_TCHAR ver[64 * sizeof(_TCHAR)];
	g_engine->showMessage(g_engine->getVersionText(ver), TEXT("TEXT ENGINE"));
	return true;
}

bool game_init(HWND)
{
	return true;
}

void game_update()
{
}

void game_end()
{
}
