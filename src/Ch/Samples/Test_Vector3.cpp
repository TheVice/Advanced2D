
#if defined(UNICODE)
#include "Advanced2d.h"
#endif

#include "Vector3.h"
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
	_tprintf(_TEXT("VECTOR TEST\n"));
	Advanced2D::Vector3<float> A(5.0f, 5.0f, 1.0f);
	_tprintf(_TEXT("A = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	Advanced2D::Vector3<float> B(90.0f, 80.0f, 1.0f);
	_tprintf(_TEXT("B = %f, %f, %f\n"), B.mX, B.mY, B.mZ);
	_tprintf(_TEXT("Distance A to B: %f\n"), A.distance2D(B));
	_tprintf(_TEXT("Length of A: %f\n"), A.length());
	_tprintf(_TEXT("Length of B: %f\n"), B.length());
	A.move(5.0f, 0.0f, 0.0f);
	_tprintf(_TEXT("A moved: %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	Advanced2D::Vector3<float> C = A;
	_tprintf(_TEXT("C = %f, %f, %f\n"), C.mX, C.mY, C.mZ);
	_tprintf(_TEXT("Dot Product of A and B: %f\n"), A.dotProduct(B));
	Advanced2D::Vector3<float> D = A.crossProduct(B);
	_tprintf(_TEXT("Cross Product of A and B: %f, %f, %f\n"), D.mX, D.mY,
	         D.mZ);
	D = A.normal();
	_tprintf(_TEXT("Normal of A: %f, %f, %f\n"), D.mX, D.mY, D.mZ);
	A.mX = 2.1f;
	A.mY = 2.2f;
	A.mZ = 2.3f;
	B.mX = 3.1f;
	B.mY = 3.2f;
	B.mZ = 3.3f;
	_tprintf(_TEXT("A = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	_tprintf(_TEXT("B = %f, %f, %f\n"), B.mX, B.mY, B.mZ);
	A += B;
	_tprintf(_TEXT("A + B = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	A -= B;
	_tprintf(_TEXT("A - B = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	A *= B;
	_tprintf(_TEXT("A * B = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	A /= B;
	_tprintf(_TEXT("A / B = %f, %f, %f\n"), A.mX, A.mY, A.mZ);
	_tprintf(_TEXT("A == B -> %s\n"), (A == B) ? _TEXT("yes") : _TEXT("no"));
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
	g_engine->shutdown();
}

void game_end()
{
}

void game_render2d()
{
}

void game_render3d()
{
}

#endif
