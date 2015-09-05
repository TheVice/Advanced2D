
#include "Advanced2D.h"
#include "Texture.h"
#include "Sprite.h"
#include <stdio.h>
#include <dinput.h>

#define OBJECT_SPRITE 100
#define MAX_PR 1000

static Advanced2D::Texture* image = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Sprite Entity Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(1024);
	Advanced2D::Engine::setScreenHeight(768);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	try
	{
		image = new Advanced2D::Texture(TEXT("asteroid.tga"), D3DCOLOR_XRGB(0, 0, 0));
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::showFatalMessage(TEXT("Unable to load asteroid.tga image"),
		                                     TEXT("game_init"));
		return false;
	}

	for (int n = 0; n < MAX_PR; ++n)
	{
		Advanced2D::Sprite* asteroid = new Advanced2D::Sprite();
		asteroid->setObjectType(OBJECT_SPRITE);
		asteroid->setImage(image);
		asteroid->setTotalFrames(64);
		asteroid->setColumns(8);
		asteroid->setSize(60, 60);
		asteroid->setPosition2D(static_cast<float>(rand() % 950),
		                        static_cast<float>(rand() % 700));
		asteroid->setFrameTimer(rand() % 100);
		asteroid->setCurrentFrame(rand() % 64);

		if (rand() % 2 == 0)
		{
			asteroid->setAnimationDirection(-1);
		}

		g_engine->addEntity(asteroid);
	}

	_TCHAR szText[32 * sizeof(_TCHAR)];
#if _MSC_VER > 1310
	_stprintf_s(szText, sizeof(szText) / sizeof(*szText), TEXT("Entities: %i"),
	            g_engine->getEntityCount());
#else
	_stprintf(szText, TEXT("Entities: %i"), g_engine->getEntityCount());
#endif
	Advanced2D::Engine::showMessage(szText);
	return true;
}

void game_update()
{
}

void game_entityUpdate(Advanced2D::Entity*) //aEntity)
{
	//Sprite *sprite = static_cast<Sprite *>(aEntity);
	//this is where you can update sprite properties
}

void game_entityRender(Advanced2D::Entity*)
{
}

void game_keyPress(int)
{
}

void game_keyRelease(int key)
{
	if (DIK_ESCAPE == key)
	{
		g_engine->shutdown();
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
}

void game_render3d()
{
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
}

void game_end()
{
	std::list<Advanced2D::Entity*> MyList = (*g_engine->getEntityList());
	std::list<Advanced2D::Entity*>::iterator iter;

	for (iter = MyList.begin(); iter != MyList.end(); ++iter)
	{
		delete (*iter);
	}

	MyList.clear();
	delete image;
	image = NULL;
}
