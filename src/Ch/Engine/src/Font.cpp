
#include "Font.h"
#include <stdio.h>
#include <exception>

namespace Advanced2D
{

Font::Font() : Sprite(), mWidths()
{
}

Font::Font(const _TCHAR* aFileName) : Sprite(), mWidths()
{
	unsigned char buffer[512];
	FILE* rfPtr = NULL;
#if _MSC_VER > 1310

	if (0 != _tfopen_s(&rfPtr, aFileName, TEXT("rb")))
#else
	if (NULL == (rfPtr = _tfopen(aFileName, TEXT("rb"))))
#endif
	{
		throw new std::exception();
	}

	fseek(rfPtr, 0, SEEK_END);

	if (512 != ftell(rfPtr))
	{
		fclose(rfPtr);
		throw new std::exception();
	}

	rewind(rfPtr);
	fread(&buffer, 512, 1, rfPtr);
	fclose(rfPtr);

	for (size_t n = 0, count = sizeof(mWidths) / sizeof(*mWidths); n < count; ++n)
	{
		mWidths[n] = static_cast<int>(buffer[n * 2]);
	}
}

void Font::print(float aX, float aY, const _TCHAR* aText, int aColor)
{
	float fx = aX;
	setColor(aColor);

	for (size_t n = 0, count = _tcslen(aText); n < count; ++n)
	{
		int frame = static_cast<int>(aText[n]);
		setCurrentFrame(frame);
		setPosition2d(fx, aY);
		draw();

		if (!mWidths[frame])
		{
			mWidths[frame] = getWidth();
		}

		fx += static_cast<float>(mWidths[frame]) * getScale();
	}
}

Font::~Font()
{
}

}
