#ifndef __WINMAIN_H_
#define __WINMAIN_H_

#include <windows.h>

LRESULT WINAPI WinProc(HWND aHwnd, UINT aMsg, WPARAM aWparam, LPARAM aLparam);
int WINAPI _tWinMain(HINSTANCE aInstance, HINSTANCE aPrevInst, LPTSTR aCmdArgs,
                     int aWinMode);

#endif
