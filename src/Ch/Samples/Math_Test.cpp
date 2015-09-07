
#if defined(UNICODE)
#include "Advanced2d.h"
#endif

#include "Mathematic.h"
#include <tchar.h>
#include <stdio.h>

#if defined(_MSC_VER)
#pragma comment(linker, "/SUBSYSTEM:\"CONSOLE\"")
#endif

int _tmain(int argc, _TCHAR* argv[])
{
#if _MSC_VER
	(void)argc;
	(void)argv;
#endif
	_tprintf(_TEXT("MATH TEST\n"));
	_tprintf(_TEXT("toDegrees\n"));

	for (double radian = 0.0, step = Advanced2D::Mathematic<double>::toRadians(0.5),
	     maxRadian = (2 * M_PI); radian < maxRadian; radian += step)
	{
		double degrees = Advanced2D::Mathematic<double>::toDegrees(radian);
		_tprintf(_TEXT("%g radians - %g degrees\n"), radian, degrees);
	}

	_tprintf(_TEXT("toRadians\n"));

	for (double degrees = 0.0, step = 0.5, maxDegrees = 360.0; degrees < maxDegrees;
	     degrees += step)
	{
		double radian = Advanced2D::Mathematic<double>::toRadians(degrees);
		_tprintf(_TEXT("%g degrees - %g radians\n"), degrees, radian);
	}

	_tprintf(_TEXT("wrapAngleRadians\n"));

	for (double radian = -(10 * M_PI),
	     step = Advanced2D::Mathematic<double>::toRadians(15), maxRadian = (10 * M_PI);
	     radian < maxRadian; radian += step)
	{
		double wrap = Advanced2D::Mathematic<double>::wrapAngleRadians(radian);
		_tprintf(_TEXT("%g input (%g degrees) - %g after wrap (%g degrees)\n"), radian,
		         Advanced2D::Mathematic<double>::toDegrees(radian), wrap,
		         Advanced2D::Mathematic<double>::toDegrees(wrap));
	}

	_tprintf(_TEXT("wrapAngleDegrees\n"));

	for (double degrees = -10 * 180, step = 15, maxDegrees = 10 * 180;
	     degrees < maxDegrees; degrees += step)
	{
		double wrap = Advanced2D::Mathematic<double>::wrapAngleDegrees(degrees);
		_tprintf(_TEXT("%g input - %g after wrap\n"), degrees, wrap);
	}

	_tprintf(_TEXT("linearVelocityX\n"));

	for (double degrees = -360, step = 15, maxDegrees = 360; degrees < maxDegrees;
	     degrees += step)
	{
		double velocity = Advanced2D::Mathematic<double>::linearVelocityX(degrees);
		_tprintf(_TEXT("%g input - %g velocity on X\n"), degrees, velocity);
	}

	_tprintf(_TEXT("linearVelocityY\n"));

	for (double degrees = -360, step = 15, maxDegrees = 360; degrees < maxDegrees;
	     degrees += step)
	{
		double velocity = Advanced2D::Mathematic<double>::linearVelocityY(degrees);
		_tprintf(_TEXT("%g input - %g velocity on Y\n"), degrees, velocity);
	}

	_tprintf(_TEXT("linearVelocity2d\n"));

	for (double degrees = -360, step = 15, maxDegrees = 360; degrees < maxDegrees;
	     degrees += step)
	{
		Advanced2D::Vector3<double> velocity =
		    Advanced2D::Mathematic<double>::linearVelocity2d(degrees);
		_tprintf(_TEXT("Liner velocity (%g degrees): %g,%g\n"), degrees, velocity.mX,
		         velocity.mY);
	}

	Advanced2D::Vector3<double> A(5, 5, 1);
	_tprintf(_TEXT("A = %g, %g, %g\n"), A.mX, A.mY, A.mZ);
	Advanced2D::Vector3<double> B(90, 80, 1);
	_tprintf(_TEXT("B = %g, %g, %g\n"), B.mX, B.mY, B.mZ);
	double angle = Advanced2D::Mathematic<double>::angleToTarget(A, B);
	_tprintf(_TEXT("\nAngle to target: %f radians (degrees %f)\n\n"), angle,
	         Advanced2D::Mathematic<double>::toDegrees(angle));
	double angle2 = Advanced2D::Mathematic<double>::angleToTarget(A.mX, A.mY, B.mX,
	                B.mY);
	_tprintf(_TEXT("%s\n"), angle == angle2 ? _TEXT("true") : _TEXT("false"));
	return 0;
}

#if defined(UNICODE)
//this #pragma comment(linker,"/ENTRY:\"wmainCRTStartup\"") do not overload project set entry,
//so use entry from lib
bool game_preload()
{
	return true;
}

bool game_init()
{
	return true;
}

void game_update()
{
	_tmain(0, NULL);
	Advanced2D::Engine::shutdown();
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

#endif
