#ifndef __WINMAIN_H_
#define __WINMAIN_H_

#include <windows.h>

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int WINAPI _tWinMain(HINSTANCE hThisInst, HINSTANCE hPrevInst, LPTSTR lpCmdArgs,
                     int nWinMode);

#endif
