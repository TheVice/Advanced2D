
#include "Advanced2D.h"
#include "Camera.h"
#include "Mesh.h"

static Advanced2D::Camera* camera = NULL;
static Advanced2D::Mesh* mesh = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("CUBE DEMO"));
	Advanced2D::Engine::setFullScreen(false);
	Advanced2D::Engine::setScreenWidth(1024);
	Advanced2D::Engine::setScreenHeight(768);
	Advanced2D::Engine::setColorDepth(32);
	return true;
}

bool game_init()
{
	mesh = new Advanced2D::Mesh(NULL);
	mesh->createCube(2.0f, 2.0f, 2.0f);
	//set the camera and perspective
	camera = new Advanced2D::Camera();
	camera->setPosition(0.0f, 2.0f, 6.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->update();
	//set the ambient color
	g_engine->setAmbient(D3DCOLOR_XRGB(40, 40, 255));
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
	//rotate and draw the cube
	mesh->rotate(2.0f, 0.0f, 0.0f);
	mesh->transform();
	mesh->draw();
}

void game_end()
{
	delete mesh;
	mesh = NULL;
	delete camera;
	camera = NULL;
}
