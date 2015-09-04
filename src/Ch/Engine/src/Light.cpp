
#include "Light.h"
#include "Advanced2D.h"

namespace Advanced2D
{

Light::Light(int aLightNum, const D3DLIGHTTYPE& aType,
             const D3DXVECTOR3& aPosition,
             const D3DXVECTOR3& aDirection, float aRange) :
	mLight(),
	mType(aType),
	mLightNum(aLightNum)
{
	mLight.Diffuse.r = mLight.Ambient.r = 1.0f;
	mLight.Diffuse.g = mLight.Ambient.g = 1.0f;
	mLight.Diffuse.b = mLight.Ambient.b = 1.0f;
	mLight.Diffuse.a = mLight.Ambient.a = 1.0f;
	mLight.Type = aType;
	mLight.Position = aPosition;
	mLight.Direction = aDirection;
	mLight.Range = aRange;

	switch (aType)
	{
		case D3DLIGHT_POINT:
			mLight.Attenuation0 = 0.01f;
			break;

		case D3DLIGHT_SPOT:
			mLight.Theta = 0.5f;
			mLight.Phi = 1.0f;
			mLight.Falloff = 1.0f;
			mLight.Attenuation0 = 1.0f;
			break;

		case D3DLIGHT_DIRECTIONAL:
			D3DXVec3Normalize(static_cast<D3DXVECTOR3*>(&mLight.Direction), &aDirection);
			break;

		case D3DLIGHT_FORCE_DWORD: //TODO:
		default:
			break;
	}

	show();
	update();
}

D3DLIGHTTYPE Light::getType()
{
	return mType;
}

D3DXVECTOR3 Light::getPosition()
{
	return mLight.Position;
}

void Light::setPosition(const D3DXVECTOR3& aPosition)
{
	mLight.Position = aPosition;
}

void Light::setPosition(float aX, float aY, float aZ)
{
	setPosition(D3DXVECTOR3(aX, aY, aZ));
}

void Light::setX(float aX)
{
	mLight.Position.x = aX;
}

float Light::getX()
{
	return mLight.Position.x;
}

void Light::setY(float aY)
{
	mLight.Position.y = aY;
}

float Light::getY()
{
	return mLight.Position.y;
}

void Light::setZ(float aZ)
{
	mLight.Position.z = aZ;
}

float Light::getZ()
{
	return mLight.Position.z;
}

D3DXVECTOR3 Light::getDirection()
{
	return mLight.Direction;
}

void Light::setDirection(const D3DXVECTOR3& aDirection)
{
	mLight.Direction = aDirection;
}

void Light::setDirection(float aX, float aY, float aZ)
{
	setDirection(D3DXVECTOR3(aX, aY, aZ));
}

D3DCOLORVALUE Light::getColor()
{
	return mLight.Diffuse;
}

void Light::setColor(const D3DCOLORVALUE& aColor)
{
	mLight.Diffuse = aColor;
}

void Light::update()
{
	g_engine->getDevice()->SetLight(mLightNum, &mLight);
}

void Light::show()
{
	g_engine->getDevice()->LightEnable(mLightNum, TRUE);
}

void Light::hide()
{
	g_engine->getDevice()->LightEnable(mLightNum, FALSE);
}

Light::~Light()
{
}

}
