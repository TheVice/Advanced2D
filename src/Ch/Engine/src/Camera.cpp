
#include "Camera.h"
#include "Advanced2D.h"
#include <cmath>

namespace Advanced2D
{

Camera::Camera() :
	mMatrixProjection(),
	mMatrixView(),
	mUpDirection(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
	mPosition(D3DXVECTOR3(0.0f, 0.0f, 10.0f)),
	mTarget(),
	mNearRange(1.0f),
	mFarRange(2000.0f),
	mAspectRatio(640.0f / 480.0f), //hard coded ratio to 1.3333 by default
	mFieldOfView(M_PI_4)
{
}

void Camera::setPerspective(float aFieldOfView, float aAspectRatio,
                            float aNearRange,
                            float aFarRange)
{
	setFieldOfView(aFieldOfView);
	setAspectRatio(aAspectRatio);
	setNearRange(aNearRange);
	setFarRange(aFarRange);
}

float Camera::getNearRange()
{
	return mNearRange;
}

void Camera::setNearRange(float aNearRange)
{
	mNearRange = aNearRange;
}

float Camera::getFarRange()
{
	return mFarRange;
}

void Camera::setFarRange(float aFarRange)
{
	mFarRange = aFarRange;
}

float Camera::getAspectRatio()
{
	return mAspectRatio;
}

void Camera::setAspectRatio(float aAspectRatio)
{
	mAspectRatio = aAspectRatio;
}

float Camera::getFieldOfView()
{
	return mFieldOfView;
}

void Camera::setFieldOfView(float aFieldOfView)
{
	mFieldOfView = aFieldOfView;
}

D3DXVECTOR3 Camera::getPosition()
{
	return mPosition;
}

void Camera::setPosition(float aX, float aY, float aZ)
{
	mPosition.x = aX;
	mPosition.y = aY;
	mPosition.z = aZ;
}


void Camera::setPosition(const D3DXVECTOR3& aPosition)
{
	setPosition(aPosition.x, aPosition.y, aPosition.z);
}

float Camera::getX()
{
	return mPosition.x;
}

void Camera::setX(float aX)
{
	mPosition.x = aX;
}

float Camera::getY()
{
	return mPosition.y;
}

void Camera::setY(float aY)
{
	mPosition.y = aY;
}

float Camera::getZ()
{
	return mPosition.z;
}

void Camera::setZ(float aZ)
{
	mPosition.z = aZ;
}

D3DXVECTOR3 Camera::getTarget()
{
	return mTarget;
}

void Camera::setTarget(const D3DXVECTOR3& aPosition)
{
	mTarget = aPosition;
}

void Camera::setTarget(float aX, float aY, float aZ)
{
	mTarget.x = aX;
	mTarget.y = aY;
	mTarget.z = aZ;
}

void Camera::update()
{
	//set the camera's perspective matrix
	D3DXMatrixPerspectiveFovLH(&mMatrixProjection, mFieldOfView,
	                           mAspectRatio, mNearRange, mFarRange);
	g_engine->getDevice()->SetTransform(D3DTS_PROJECTION, &mMatrixProjection);
	//set the camera's view matrix
	D3DXMatrixLookAtLH(&mMatrixView, &mPosition, &mTarget,
	                   &mUpDirection);
	g_engine->getDevice()->SetTransform(D3DTS_VIEW, &mMatrixView);
}

Camera::~Camera()
{
}

}
