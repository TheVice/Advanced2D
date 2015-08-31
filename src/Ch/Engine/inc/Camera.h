#ifndef __CAMERA_H_
#define __CAMERA_H_

#include <d3dx9.h>

namespace Advanced2D
{
class Camera
{
private:
	D3DXMATRIX mMatrixProjection;
	D3DXMATRIX mMatrixView;
	D3DXVECTOR3 mUpDirection;
	D3DXVECTOR3 mPosition;
	D3DXVECTOR3 mTarget;

	float mNearRange;
	float mFarRange;
	float mAspectRatio;
	float mFieldOfView;

	Camera(const Camera& aRhs);
	Camera& operator=(const Camera& aRhs);
public:
	Camera();
	void setPerspective(float aFieldOfView, float aAspectRatio, float aNearRange,
	                    float aFarRange);
	float getNearRange();
	void setNearRange(float aNearRange);
	float getFarRange();
	void setFarRange(float aFarRange);
	float getAspectRatio();
	void setAspectRatio(float aAspectRatio);
	float getFieldOfView();
	void setFieldOfView(float aFieldOfView);

	D3DXVECTOR3 getPosition();
	void setPosition(float aX, float aY, float aZ);
	void setPosition(const D3DXVECTOR3& aPosition);
	float getX();
	void setX(float aX);
	float getY();
	void setY(float aY);
	float getZ();
	void setZ(float aZ);

	D3DXVECTOR3 getTarget();
	void setTarget(const D3DXVECTOR3& aPosition);
	void setTarget(float aX, float aY, float aZ);

	void update();

	virtual ~Camera();
};
}

#endif
