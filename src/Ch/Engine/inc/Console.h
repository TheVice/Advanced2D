#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include <tchar.h>
#include <vector>
#include <string>

namespace Advanced2D
{
class Sprite;
class Font;
class Console
{
private:
	bool mShowing;
	Sprite* mPanel;
	Font* mFont;
#ifndef UNICODE
	std::vector<std::string> mTextLines;
	std::vector<std::string>::iterator iter;
#else
	std::vector<std::wstring> mTextLines;
	std::vector<std::wstring>::iterator iter;
#endif
public:
	Console();
	void draw();
	void print(const _TCHAR* aText, int aLine = -1);
	bool isShowing();
	void setShowing(bool aShowing);
	void clear();
	virtual ~Console();
};
}

#endif
