#ifndef __FONT_H_
#define __FONT_H_

#include "Sprite.h"

namespace Advanced2D
{
class Font : public Sprite
{
private:
	int mWidths[256];
	Font(const Font& aRhs);
	Font& operator=(const Font& aRhs);
public:
	Font();
	Font(const _TCHAR* aFileName);
	void print(float aX, float aY, const _TCHAR* aText, int aColor = 0xFFFFFFFF);
	virtual ~Font();
};
}

#endif
