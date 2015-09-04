#ifndef __TEXTURE_H_
#define __TEXTURE_H_

#include <tchar.h>
#include <d3dx9.h>

namespace Advanced2D
{
class Texture
{
private:
	LPDIRECT3DTEXTURE9 mTexture;
	D3DXIMAGE_INFO mInfo;

	Texture();
	Texture(const Texture& aRhs);
	Texture& operator=(const Texture& aRhs);
public:
	Texture(const _TCHAR* aFileName, D3DCOLOR aTransColor);
	LPDIRECT3DTEXTURE9 getTexture();
	int getWidth();
	int getHeight();
	virtual ~Texture();
};
}

#endif
