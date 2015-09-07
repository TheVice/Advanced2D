
#include "Console.h"
#include "Font.h"
#include "Advanced2D.h"

namespace Advanced2D
{

Console::Console() :
	mShowing(false),
	mPanel(NULL),
	mFont(NULL),
	mTextLines()
{
	//load the panel image
	mPanel = new Sprite();

	if (!mPanel->loadImage(TEXT("panel.tga")))
	{
		throw new std::exception();
	}

	mPanel->setScale(static_cast<float>(Engine::getScreenWidth()) / 640.0f);
	mPanel->setColor(0x99FFFFFF);
	//load the font
	mFont = new Font(TEXT("system12.dat"));

	if (!mFont->loadImage(TEXT("system12.tga")))
	{
		throw new std::exception();
	}

	mFont->setColumns(16);
	mFont->setSize(14, 16);
	clear();
}

void Console::draw()
{
	size_t x = 5, y = 0;

	if (!mShowing)
	{
		return;
	}

	//draw panel background
	mPanel->draw();

	//draw text lines
	for (size_t n = 0, count = mTextLines.size(); n < count; ++n)
	{
		if ((mTextLines[n].length() + 1) < 2)
		{
			continue;
		}

		mFont->print(static_cast<float>(x), static_cast<float>(y * 14),
		             mTextLines[n].c_str(), 0xFF000000);
		y += 1;

		if (y > 26)
		{
			if (x > 10)
			{
				break;
			}

			x = static_cast<size_t>(g_engine->getScreenWidth() / 2 + 5);
			y = 0;
		}
	}
}

void Console::print(const _TCHAR* aText, int aLine)
{
	static size_t currentLine = 0;
#ifndef UNICODE
	std::string s(aText);
#else
	std::wstring s(aText);
#endif

	if (aLine > -1)
	{
		currentLine = static_cast<size_t>(aLine);
	}

	mTextLines[currentLine] = s;

	if (currentLine++ > 52)
	{
		currentLine = 0;
	}
}

bool Console::isShowing()
{
	return mShowing;
}

void Console::setShowing(bool aShowing)
{
	mShowing = aShowing;
}

void Console::clear()
{
	for (int n = 0; n < 55; ++n)
	{
		mTextLines.push_back(TEXT(""));
	}
}

Console::~Console()
{
	delete mPanel;
	delete mFont;
}

}
