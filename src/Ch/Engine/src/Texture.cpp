
#include "Texture.h"
#include "Advanced2D.h"

namespace Advanced2D
{

Texture::Texture(const _TCHAR* aFileName, D3DCOLOR aTransColor) :
	mTexture(NULL),
	mInfo()
{
	//get width and height from bitmap file
	if (FAILED(D3DXGetImageInfoFromFile(aFileName, &mInfo)))
	{
		throw new std::exception();
	}

	//create the new texture by loading a bitmap image file
	if (FAILED(D3DXCreateTextureFromFileEx(
	               g_engine->getDevice(),  //Direct3D device object
	               aFileName,              //bitmap filename
	               mInfo.Width,            //bitmap image width
	               mInfo.Height,           //bitmap image height
	               1,                      //mip-map levels (1 for no chain)
	               D3DPOOL_DEFAULT,        //the type of surface (standard)
	               D3DFMT_UNKNOWN,         //surface format (default)
	               D3DPOOL_DEFAULT,        //memory class for the texture
	               D3DX_DEFAULT,           //image filter
	               D3DX_DEFAULT,           //mip filter
	               aTransColor,            //color key for transparency
	               &mInfo,                 //bitmap file info (from loaded file)
	               NULL,                   //color palette
	               &mTexture )))           //destination texture
	{
		throw new std::exception();
	}
}

LPDIRECT3DTEXTURE9 Texture::getTexture()
{
	return mTexture;
}

int Texture::getWidth()
{
	return mInfo.Width;
}

int Texture::getHeight()
{
	return mInfo.Height;
}

Texture::~Texture()
{
	mTexture->Release();
}

}
