#ifndef __SPRITE_H_
#define __SPRITE_H_

#include "Entity.h"
#include "Vector3.h"
#include <d3dx9.h>

namespace Advanced2D
{
class Texture;
enum CollisionType
{
	COLLISION_NONE = 0,
	COLLISION_RECT = 1,
	COLLISION_DIST = 2
};

class Sprite : public Entity
{
private:
	bool mImageLoaded;
	Texture* mImage;
	Vector3<int> mSize;
	Vector3<float> mPosition;
	Vector3<float> mVelocity;
	int mState;
	int mDirection;
	int mFrameStart;
	int mFrameTimer;
	int mCurrentFrame;
	int mTotalFrames;
	int mAnimColumns;
	Vector3<int> mAnimStart;
	int mAnimDirection;
	float mRotation;
	float mScale;
	D3DCOLOR mColor;
	bool mCollidable;
	enum CollisionType mCollisionMethod;
	D3DXMATRIX mMatRotate;
	D3DXMATRIX mMatScale;
	int mMoveStart;
	int mMoveTimer;
	float mFaceAngle;
	float mMoveAngle;

	Sprite(const Sprite& aRhs);
	Sprite& operator=(const Sprite& aRhs);
protected:
	void transform();
public:
	Sprite();

	bool loadImage(const _TCHAR* aFileName,
	               D3DCOLOR aTransColor = D3DCOLOR_XRGB(255, 0,
	                                      255));
	void setImage(Texture* aImage);

	//image size
	void setSize(int aWidth, int aHeight);
	void setWidth(int aWidth);
	int getWidth();
	void setHeight(int aHeight);
	int getHeight();

	//screen position
	Vector3<float>& getPosition();
	void setPosition2D(const Vector3<float>& aPosition2D);
	void setPosition2D(float aPositionX, float aPositionY);

	//movement velocity
	Vector3<float>& getVelocity();
	void setVelocity(const Vector3<float>& aVelocity);
	void setVelocity(float aVelocityX, float aVelocityY);

	int getState();
	void setState(int aState);

	int getDirection();
	void setDirection(int aDirection);

	int getFrameTimer();
	void setFrameTimer(int aFrameTimer);

	int getCurrentFrame();
	void setCurrentFrame(int aCurrentFrame);

	int getTotalFrames();
	void setTotalFrames(int aTotalFrames);

	int getColumns();
	void setColumns(int aAnimColumns);

	int getAnimationDirection();
	void setAnimationDirection(int aAnimationDirection);

	float getRotation();
	void setRotation(float aRotation);

	float getScale();
	void setScale(float aScale);

	D3DCOLOR getColor();
	void setColor(const D3DCOLOR& aColor);

	int getMoveTimer();
	void setMoveTimer(int aMoveTimer);

	bool isCollidable();
	void setCollidable(bool aCollidable);

	CollisionType getCollisionMethod();
	void setCollisionMethod(CollisionType aCollisionType);

	void move();
	void animate();
	void draw();

	virtual ~Sprite();
};
}

#endif
