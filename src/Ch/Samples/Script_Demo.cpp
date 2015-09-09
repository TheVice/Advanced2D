
#include "Advanced2D.h"
#include "Font.h"
#include "LuaScript.h"
#include <dinput.h>

/*
--script.lua
PROGRAMTITLE = "SCRIPT DEMO"
FULLSCREEN = false
SCREENWIDTH = 640
SCREENHEIGHT = 480
COLORDEPTH = 32
*/

static Advanced2D::Font* font = NULL;
static Advanced2D::LuaScript script;
#ifdef UNICODE
static wchar_t* title;
#else
static char* title;
#endif


bool game_preload()
{
	if (!script.loadScript("script.lua"))
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load script.lua file"),
		                                     TEXT("game_preload"));
		return false;
	}

	const char* titleTmp = script.getGlobalString("PROGRAMTITLE");

	if (!titleTmp)
	{
		return false;
	}

	size_t iTitleLength = strlen(titleTmp);

	if (!iTitleLength)
	{
		return false;
	}

#ifndef UNICODE
	title = new char[iTitleLength + 1];
#if _MSC_VER > 1310
	strcpy_s(title, iTitleLength + 1, titleTmp);
#else
	strcpy(title, titleTmp);
#endif
	title[iTitleLength] = '\0';
#else
	title = new wchar_t[iTitleLength + 1];
	MultiByteToWideChar(CP_ACP, 0, titleTmp, static_cast<int>(iTitleLength), title,
	                    static_cast<int>(iTitleLength));
	title[iTitleLength] = '\0';
#endif
	int width = static_cast<int>(script.getGlobalNumber("SCREENWIDTH"));
	int height = static_cast<int>(script.getGlobalNumber("SCREENHEIGHT"));
	int depth = static_cast<int>(script.getGlobalNumber("COLORDEPTH"));
	bool fullscreen = script.getGlobalBoolean("FULLSCREEN");
	Advanced2D::Engine::setAppTitle(title);
	Advanced2D::Engine::setFullScreen(fullscreen);
	Advanced2D::Engine::setScreenWidth(width);
	Advanced2D::Engine::setScreenHeight(height);
	Advanced2D::Engine::setColorDepth(depth);
	return true;
}

bool game_init()
{
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
	switch (aKey)
	{
		case DIK_ESCAPE:
			Advanced2D::Engine::shutdown();
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
	font->print(10, 20, title);
	_TCHAR szText[64 * sizeof(_TCHAR)];
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Screen Width: %i"),
	            Advanced2D::Engine::getScreenWidth());
#else
	_stprintf(szText, TEXT("Screen Width: %i"),
	          Advanced2D::Engine::getScreenWidth());
#endif
	font->print(10, 40, szText);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Screen Height: %i"),
	            Advanced2D::Engine::getScreenHeight());
#else
	_stprintf(szText, TEXT("Screen Height: %i"),
	          Advanced2D::Engine::getScreenHeight());
#endif
	font->print(10, 60, szText);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Screen Depth: %i"),
	            Advanced2D::Engine::getColorDepth());
#else
	_stprintf(szText, TEXT("Screen Depth: %i"),
	          Advanced2D::Engine::getColorDepth());
#endif
	font->print(10, 80, szText);
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText),
	            TEXT("Screen FullScreen: %s"),
	            Advanced2D::Engine::getFullScreen() ? TEXT("yes") : TEXT("no"));
#else
	_stprintf(szText, TEXT("Screen FullScreen: %s"),
	          Advanced2D::Engine::getFullScreen() ? TEXT("yes") : TEXT("no"));
#endif
	font->print(10, 100, szText);
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
	g_engine->setIdentity();
}

void game_end()
{
	delete title;
	title = NULL;
	delete font;
	font = NULL;
}
