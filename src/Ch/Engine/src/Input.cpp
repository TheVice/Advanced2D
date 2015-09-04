
#include "Input.h"

namespace Advanced2D
{

Input::Input(HWND aWindow) :
	mWindow(aWindow),
	mDirectInput(NULL),
	mKeyboard(NULL),
	mKeyState(),
	mMouse(NULL),
	mMouseState(),
	mPosition()
{
	DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION,
	                   IID_IDirectInput8, reinterpret_cast<void**>(&mDirectInput), NULL);
	mDirectInput->CreateDevice(GUID_SysKeyboard, &mKeyboard, NULL);
	mKeyboard->SetDataFormat(&c_dfDIKeyboard);
	mKeyboard->SetCooperativeLevel(mWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mKeyboard->Acquire();
	mDirectInput->CreateDevice(GUID_SysMouse, &mMouse, NULL);
	mMouse->SetDataFormat(&c_dfDIMouse);
	mMouse->SetCooperativeLevel(mWindow, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	mMouse->Acquire();
}

void Input::update()
{
	mKeyboard->Poll();

	if (FAILED(mKeyboard->GetDeviceState(256, static_cast<LPVOID>(&mKeyState))))
	{
		mKeyboard->Acquire();
	}

	mMouse->Poll();

	if (FAILED(mMouse->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState)))
	{
		mMouse->Acquire();
	}

	GetCursorPos(&mPosition);
	ScreenToClient(mWindow, &mPosition);
}

bool Input::getMouseButton(unsigned char aButton)
{
	return (mMouseState.rgbButtons[aButton] & 0x80) ? true : false;
}

unsigned char Input::getKeyState(int aKey)
{
	return mKeyState[aKey];
}

long Input::getPosX()
{
	return mPosition.x;
}

long Input::getPosY()
{
	return mPosition.y;
}

long Input::getDeltaX()
{
	return mMouseState.lX;
}

long Input::getDeltaY()
{
	return mMouseState.lY;
}

long Input::getDeltaWheel()
{
	return mMouseState.lZ;
}

Input::~Input()
{
	if (mDirectInput)
	{
		mDirectInput->Release();
	}

	if (mKeyboard)
	{
		mKeyboard->Release();
	}

	if (mMouse)
	{
		mMouse->Release();
	}
}

}
