
#include "Advanced2D.h"
#include "Camera.h"
#include "Mesh.h"
#include <vector>

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0)

static Advanced2D::Camera* camera = NULL;

#define SPHERES 100

typedef std::vector<Advanced2D::Mesh*>::iterator iter;
static std::vector<Advanced2D::Mesh*> entities;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("BOUNCING BALLS"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(1024);
	Advanced2D::Engine::setScreenHeight(768);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	//set the camera and perspective
	camera = new Advanced2D::Camera();
	camera->setPosition(0.0f, 2.0f, 10.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->update();

	//create ball meshes
	for (int n = 0; n < SPHERES; ++n)
	{
		Advanced2D::Mesh* ball = NULL;

		try
		{
			ball = new Advanced2D::Mesh(TEXT("ball.x"));
		}
		catch (const std::exception&)
		{
			Advanced2D::Engine::showFatalMessage(TEXT("Unable to load ball.x mesh"),
			                                     TEXT("game_init"));
			return false;
		}

		ball->setScale(0.3f, 0.3f, 0.3f);
		ball->setPosition(0.0f, 0.0f, 0.0f);
		ball->setVelocity((rand() % 8 + 1) / 100.0f, (rand() % 8 + 1) / 100.0f,
		                  (rand() % 8 + 1) / 100.0f);
		ball->setRotation(0.1f, 0.2f, 0.01f);
		entities.push_back(ball);
	}

	return true;
}

void game_update()
{
	for (iter i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->move();
		(*i)->limitBoundary(-5, 5, 4, -4, 4, -4);
	}

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
}

void game_render3d()
{
	//clear the scene using a dark blue color
	g_engine->clearScene(D3DCOLOR_RGBA(30, 30, 100, 0));
	//return to the origin
	g_engine->setIdentity();

	//draw entities
	for (iter i = entities.begin(); i != entities.end(); ++i)
	{
		(*i)->transform();
		(*i)->draw();
	}
}

void game_end()
{
	delete camera;
	camera = NULL;

	for (iter i = entities.begin(); i != entities.end(); ++i)
	{
		delete (*i);
	}

	entities.clear();
}
