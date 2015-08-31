#ifndef __LIGHT_H_
#define __LIGHT_H_

#include <d3dx9.h>

namespace Advanced2D
{
class Light
{
private:
	D3DLIGHT9 mLight;
	D3DLIGHTTYPE mType;
	int mLightNum;

	Light();
	Light(const Light& aRhs);
	Light& operator=(const Light& aRhs);
public:
	Light(int aLightNum, const D3DLIGHTTYPE& aType, const D3DXVECTOR3& aPosition,
	      const D3DXVECTOR3& aDirection, float aRange);

	D3DLIGHTTYPE getType();

	D3DXVECTOR3 getPosition();
	void setPosition(const D3DXVECTOR3& aPosition);
	void setPosition(float aX, float aY, float aZ);
	void setX(float aX);
	float getX();
	void setY(float aY);
	float getY();
	void setZ(float aZ);
	float getZ();

	D3DXVECTOR3 getDirection();
	void setDirection(const D3DXVECTOR3& aDirection);
	void setDirection(float aX, float aY, float aZ);

	D3DCOLORVALUE getColor();
	void setColor(const D3DCOLORVALUE& aColor);

	void update();
	void show();
	void hide();

	virtual ~Light();
};
}

#endif
