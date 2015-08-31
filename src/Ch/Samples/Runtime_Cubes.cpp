
#include "Advanced2D.h"
#include "Camera.h"
#include "Mesh.h"

using namespace Advanced2D;

static Camera* camera = NULL;
static Mesh* mesh = NULL;

bool game_preload()
{
	g_engine->setAppTitle(TEXT("CUBE DEMO"));
	g_engine->setFullScreen(false);
	g_engine->setScreenWidth(1024);
	g_engine->setScreenHeight(768);
	g_engine->setColorDepth(32);
	return true;
}

bool game_init()
{
	mesh = new Mesh(NULL);
	mesh->createCube(2.0f, 2.0f, 2.0f);
	//set the camera and perspective
	camera = new Camera();
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
	delete camera;
}
