
#include "winmain.h"
#include "Advanced2D.h"
#include <time.h>
#include <stdio.h>

static HINSTANCE g_hIstance;
static HWND g_hWnd = NULL;
static int g_nCmdShow;
Advanced2D::Engine* g_engine;

bool gameover;

/*EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)*/

int WINAPI _tWinMain(HINSTANCE hThisInst, HINSTANCE/*hPrevInst*/,
                     LPTSTR/*lpCmdArgs*/, int nWinMode)
{
	MSG msg;
	srand((unsigned int)time(NULL));
	g_hIstance = hThisInst;
	g_nCmdShow = nWinMode;
	DWORD dwStyle, dwExStyle;
	RECT windowRect;
	g_engine = new Advanced2D::Engine();

	if (!game_preload())
	{
		g_engine->Close();
		MessageBox(g_hWnd, TEXT("Error in game preload!"), TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	TCHAR szTitle[MAX_PATH];
	g_engine->getAppTitle(szTitle);
	windowRect.left = 0L;
	windowRect.right = static_cast<long>(g_engine->getScreenWidth());
	windowRect.top = 0L;
	windowRect.bottom = static_cast<long>(g_engine->getScreenHeight());
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hThisInst;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szTitle;
	wc.hIconSm = NULL;

	if (!RegisterClassEx(&wc))
	{
		g_engine->Close();
		MessageBox(g_hWnd, TEXT("Error while processing RegisterClassEx!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	DEVMODE dm;
	memset(&dm, 0, sizeof(DEVMODE));
	dm.dmSize = sizeof(DEVMODE);
	dm.dmPelsWidth = g_engine->getScreenWidth();
	dm.dmPelsHeight = g_engine->getScreenHeight();
	dm.dmBitsPerPel = g_engine->getColorDepth();
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	if (g_engine->getFullScreen() &&
	    DISP_CHANGE_SUCCESSFUL == ChangeDisplaySettings(&dm, CDS_FULLSCREEN))
	{
		dwStyle = WS_POPUP;
		dwExStyle = WS_EX_APPWINDOW;
		ShowCursor(FALSE);
	}
	else
	{
		dwStyle = WS_OVERLAPPEDWINDOW;
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		g_engine->setFullScreen(false);
	}

	AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);
	g_hWnd = CreateWindowEx(0, szTitle, szTitle,
	                        dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
	                        0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,
	                        HWND_DESKTOP, NULL, g_hIstance, NULL);

	if (!g_hWnd)
	{
		g_engine->Close();
		MessageBox(g_hWnd, TEXT("Error while processing CreateWindowEx!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	ShowWindow(g_hWnd, g_nCmdShow);
	UpdateWindow(g_hWnd);
	g_engine->setWindowHandle(g_hWnd);

	if (!g_engine->Init(g_engine->getScreenWidth(), g_engine->getScreenHeight(),
	                    g_engine->getColorDepth(), g_engine->getFullScreen()))
	{
		g_engine->Close();
		MessageBox(g_hWnd, TEXT("Error while processing g_engine::Init!"),
		           TEXT("Error"), MB_ICONERROR);
		return -1;
	}

	gameover = false;

	while (!gameover)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		g_engine->Update();
	}

	if (g_engine->getFullScreen())
	{
		ShowCursor(TRUE);
	}

	g_engine->Close();
	delete g_engine;
	g_engine = NULL;
	return 0;
}

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_QUIT:
		case WM_CLOSE:
		case WM_DESTROY:
			g_engine->Shutdown();
			break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
