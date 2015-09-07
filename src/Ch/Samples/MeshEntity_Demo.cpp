
#include "Advanced2D.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"
#include <dinput.h>

#define SCREENW 1024
#define SCREENH 768
#define MAX_PR 10

static Advanced2D::Camera* camera = NULL;
static Advanced2D::Light* light = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("Mesh Entity Demo"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(SCREENW);
	Advanced2D::Engine::setScreenHeight(SCREENH);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	camera = new Advanced2D::Camera();
	camera->setPosition(0.0f, 2.0f, 50.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->update();
	light = new Advanced2D::Light(0, D3DLIGHT_DIRECTIONAL, D3DXVECTOR3(0.0f, 0.0f,
	                              0.0f),
	                              D3DXVECTOR3(1.0f, 0.0f, 0.0f), 100.0);
	light->setColor(D3DXCOLOR(1, 0, 0, 0));
	g_engine->setAmbient(D3DCOLOR_ARGB(0, 0, 0, 0));

	for (int n = 0; n < MAX_PR; ++n)
	{
		Advanced2D::Mesh* mesh = NULL;

		try
		{
			mesh = new Advanced2D::Mesh(TEXT("cytovirus.x"));
		}
		catch (const std::exception&)
		{
			Advanced2D::Engine::showFatalMessage(TEXT("Unable to load cytovirus.x mesh"),
			                                     TEXT("game_init"));
			return false;
		}

		mesh->setScale(0.02f, 0.02f, 0.02f);
		mesh->setPosition(static_cast<float>(rand() % 40 - 20),
		                  static_cast<float>(rand() % 40 - 20), static_cast<float>(rand() % 10 - 5));
		g_engine->addEntity(mesh);
	}

	return true;
}

void game_update()
{
}

void game_entityUpdate(Advanced2D::Entity* aEntity)
{
	if (aEntity->getRenderType() == Advanced2D::RENDER3D)
	{
		Advanced2D::Mesh* mesh = static_cast<Advanced2D::Mesh*>(aEntity);
		mesh->rotate(0.0f, 0.2f, 0.0f);
	}
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
	g_engine->setIdentity();
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
	delete camera;
	camera = NULL;
	delete light;
	light = NULL;
}
