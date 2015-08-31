
#include "winmain.h"
#include "Advanced2D.h"
#include <time.h>
#include <stdio.h>

Advanced2D::Engine* g_engine = NULL;
bool gameover = false;

int WINAPI _tWinMain(HINSTANCE aInstance, HINSTANCE aPrevInst, LPTSTR aCmdArgs,
                     int aWinMode)
{
	(void)aPrevInst;
	(void)aCmdArgs;
	srand((unsigned int)time(NULL));

	if (!game_preload())
	{
		Advanced2D::Engine::close();
		MessageBox(HWND_DESKTOP, TEXT("Error in game preload!"), TEXT("Error"),
		           MB_ICONERROR);
		return -1;
	}

	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = aInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = TEXT("Advanced2D");
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc))
	{
		Advanced2D::Engine::close();
		MessageBox(HWND_DESKTOP, TEXT("Error while processing RegisterClassEx!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	DEVMODE deviceMode;
	memset(&deviceMode, 0, sizeof(DEVMODE));
	deviceMode.dmSize = sizeof(DEVMODE);
	deviceMode.dmPelsWidth = Advanced2D::Engine::getScreenWidth();
	deviceMode.dmPelsHeight = Advanced2D::Engine::getScreenHeight();
	deviceMode.dmBitsPerPel = Advanced2D::Engine::getColorDepth();
	deviceMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	DWORD dwStyle = 0;
	DWORD dwExStyle = 0;

	if (Advanced2D::Engine::getFullScreen() &&
	    DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(&deviceMode, CDS_FULLSCREEN))
	{
		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_APPWINDOW;
		ShowCursor(FALSE);
	}
	else
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		Advanced2D::Engine::setFullScreen(false);
	}

	RECT windowRect;
	windowRect.left = 0L;
	windowRect.right = static_cast<long>(Advanced2D::Engine::getScreenWidth());
	windowRect.top = 0L;
	windowRect.bottom = static_cast<long>(Advanced2D::Engine::getScreenHeight());
	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	//
	HWND hwnd = CreateWindowEx(0, wc.lpszClassName,
	                           Advanced2D::Engine::getAppTitle(),
	                           dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	                           0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
	                           HWND_DESKTOP, NULL, aInstance, NULL);

	if (!hwnd)
	{
		Advanced2D::Engine::close();
		MessageBox(HWND_DESKTOP, TEXT("Error while processing CreateWindowEx!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	try
	{
		g_engine = new Advanced2D::Engine(hwnd);
	}
	catch (const std::exception&)
	{
		Advanced2D::Engine::close();
		MessageBox(HWND_DESKTOP, TEXT("Error while creating engine!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	if (!game_init())
	{
		Advanced2D::Engine::close();
		MessageBox(HWND_DESKTOP, TEXT("Error while game_init!"),
		           TEXT("Error"), MB_ICONERROR);
	}

	ShowWindow(hwnd, aWinMode);
	UpdateWindow(hwnd);

	while (!gameover)
	{
		MSG msg;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_engine->update();
	}

	if (Advanced2D::Engine::getFullScreen())
	{
		ShowCursor(TRUE);
	}

	Advanced2D::Engine::close();
	delete g_engine;
	g_engine = NULL;
	return 0;
}

LRESULT WINAPI WinProc(HWND aHwnd, UINT aMsg, WPARAM aWparam, LPARAM aLparam)
{
	switch (aMsg)
	{
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			Advanced2D::Engine::shutdown();
			break;
	}

	return DefWindowProc(aHwnd, aMsg, aWparam, aLparam);
}
