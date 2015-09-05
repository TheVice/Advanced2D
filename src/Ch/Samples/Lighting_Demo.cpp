
#include "Advanced2D.h"
#include "Camera.h"
#include "Light.h"
#include "Mesh.h"

#define DIRECTLIGHT
//#define SPOTLIGHT
//#define POINTLIGHT

#define KEY_DOWN(vk) ((GetAsyncKeyState(vk) & 0x8000) ? 1 : 0)

static Advanced2D::Camera* camera = NULL;
static Advanced2D::Light* light = NULL;
static Advanced2D::Mesh* mesh = NULL;

bool game_preload()
{
	Advanced2D::Engine::setAppTitle(TEXT("LIGHTING DEMO"));
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
	camera->setPosition(0.0f, 2.0f, 40.0f);
	camera->setTarget(0.0f, 0.0f, 0.0f);
	camera->update();

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

	mesh->setScale(0.1f, 0.1f, 0.1f);
#if defined(DIRECTLIGHT)
	//create a directional light
	light = new Advanced2D::Light(0, D3DLIGHT_DIRECTIONAL, D3DXVECTOR3(0.0f, 0.0f,
	                              0.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), 100.0f);
#else
#if defined(SPOTLIGHT)
	//create the spot light
	light = new Advanced2D::Light(0, D3DLIGHT_SPOT, D3DXVECTOR3(-10.0f, -20.0f,
	                              0.0f), D3DXVECTOR3(0.0f, 2.0f, 0.0f), 1000.0f);
#else
#if defined(POINTLIGHT)
	//create the point light
	light = new Advanced2D::Light(0, D3DLIGHT_POINT, D3DXVECTOR3(0.0f, -22.0f,
	                              0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 20.0f);
#endif
#endif
#endif
	//set a low ambient level
	g_engine->setAmbient(D3DCOLOR_XRGB(20, 20, 20));
	return true;
}

void game_update()
{
	//rotate the mesh
	mesh->rotate(-0.1f, 0.0f, 0.05f);

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
	g_engine->clearScene(D3DCOLOR_XRGB(0, 0, 80));
	//return to the origin
	g_engine->setIdentity();
	mesh->transform();
	mesh->draw();
}

void game_end()
{
	delete camera;
	camera = NULL;
	delete mesh;
	mesh = NULL;
	delete light;
	light = NULL;
}
