#ifndef __INPUT_H_
#define __INPUT_H_

#include <dinput.h>

namespace Advanced2D
{
class Input
{
private:
	HWND mWindow;
	IDirectInput8* mDirectInput;
	IDirectInputDevice8* mKeyboard;
	unsigned char mKeyState[256];
	IDirectInputDevice8* mMouse;
	DIMOUSESTATE mMouseState;
	POINT mPosition;

	Input();
	Input(const Input& aRhs);
	Input& operator=(const Input& aRhs);
public:
	Input(HWND aWindow);
	void update();
	bool getMouseButton(unsigned char aButton);
	unsigned char getKeyState(int aKey);
	long getPosX();
	long getPosY();
	long getDeltaX();
	long getDeltaY();
	long getDeltaWheel();
	virtual ~Input();
};
}

#endif
