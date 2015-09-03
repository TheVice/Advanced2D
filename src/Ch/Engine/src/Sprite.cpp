
#include "Sprite.h"
#include "Advanced2D.h"
#include "Texture.h"

namespace Advanced2D
{

void Sprite::transform()
{
	D3DXMATRIX mat;
	D3DXVECTOR2 scale(mScale, mScale);
	D3DXVECTOR2 center((mSize.mX * mScale) / 2, (mSize.mY * mScale) / 2);
	D3DXVECTOR2 trans(mPosition.mX, mPosition.mY);
	D3DXMatrixTransformation2D(&mat, NULL, 0.0f, &scale, &center, mRotation,
	                           &trans);
	g_engine->getSpriteHandler()->SetTransform(&mat);
}

Sprite::Sprite() :
	mImageLoaded(false),
	mImage(NULL),
	mSize(1, 1, 0),
	mPosition(),
	mVelocity(),
	mVisible(true),
	mAlive(true),
	mState(0),
	mDirection(0),
	mFrameStart(0),
	mFrameTimer(0),
	mCurrentFrame(0),
	mTotalFrames(1),
	mAnimColumns(1),
	mAnimStart(),
	mAnimDirection(1),
	mRotation(0),
	mScale(1),
	mColor(0xFFFFFFFF),
	mCollidable(true),
	mCollisionMethod(COLLISION_RECT),
	mMatRotate(),
	mMatScale(),
	mLifetimeLength(0),
	mObjectType(0),
	mLifeTimeTimer(),
	mMoveStart(0),
	mMoveTimer(16),
	mFaceAngle(0),
	mMoveAngle(0)
{
}

bool Sprite::loadImage(const _TCHAR* aFileName, D3DCOLOR aTransColor)
{
	//if image already exists, free it
	if (mImageLoaded)
	{
		delete mImage;
		mImage = NULL;
		mImageLoaded = false;
	}

	try
	{
		mImage = new Texture(aFileName, aTransColor);
		mImageLoaded = true;
	}
	catch (const std::exception&)
	{
		mImageLoaded = false;
	}

	if (mImageLoaded)
	{
		setSize(mImage->getWidth(), mImage->getHeight());
		return true;
	}

	return false;
}

void Sprite::setImage(Texture* aImage)
{
	if (!mImageLoaded && aImage)
	{
		mImage = aImage;
		setWidth(mImage->getWidth());
		setHeight(mImage->getHeight());
		mImageLoaded = false;
	}
}

void Sprite::setSize(int aWidth, int aHeight)
{
	mSize.mX = aWidth;
	mSize.mY = aHeight;
}

void Sprite::setWidth(int aWidth)
{
	mSize.mX = aWidth;
}

int Sprite::getWidth()
{
	return mSize.mX;
}

void Sprite::setHeight(int aHeight)
{
	mSize.mY = aHeight;
}

int Sprite::getHeight()
{
	return mSize.mY;
}

Vector3<float>& Sprite::getPosition()
{
	return mPosition;
}

void Sprite::setPosition2D(const Vector3<float>& aPosition2D)
{
	mPosition = aPosition2D;
}

void Sprite::setPosition2D(float aPositionX, float aPositionY)
{
	mPosition.mX = aPositionX;
	mPosition.mY = aPositionY;
}

Vector3<float>& Sprite::getVelocity()
{
	return mVelocity;
}

void Sprite::setVelocity(const Vector3<float>& aVelocity)
{
	mVelocity = aVelocity;
}

void Sprite::setVelocity(float aVelocityX, float aVelocityY)
{
	mVelocity.mX = aVelocityX;
	mVelocity.mY = aVelocityY;
}

bool Sprite::isVisible()
{
	return mVisible;
}

void Sprite::setVisible(bool aVisible)
{
	mVisible = aVisible;
}

bool Sprite::isAlive()
{
	return mAlive;
}

void Sprite::setAlive(bool aAlive)
{
	mAlive = aAlive;
}

int Sprite::getState()
{
	return mState;
}

void Sprite::setState(int aState)
{
	mState = aState;
}

int Sprite::getDirection()
{
	return mDirection;
}

void Sprite::setDirection(int aDirection)
{
	mDirection = aDirection;
}

int Sprite::getFrameTimer()
{
	return mFrameTimer;
}

void Sprite::setFrameTimer(int aFrameTimer)
{
	mFrameTimer = aFrameTimer;
}

int Sprite::getCurrentFrame()
{
	return mCurrentFrame;
}

void Sprite::setCurrentFrame(int aCurrentFrame)
{
	mCurrentFrame = aCurrentFrame;
}

int Sprite::getTotalFrames()
{
	return mTotalFrames;
}

void Sprite::setTotalFrames(int aTotalFrames)
{
	mTotalFrames = aTotalFrames;
}

int Sprite::getColumns()
{
	return mAnimColumns;
}

void Sprite::setColumns(int aAnimColumns)
{
	mAnimColumns = aAnimColumns;
}

int Sprite::getAnimationDirection()
{
	return mAnimDirection;
}

void Sprite::setAnimationDirection(int aAnimationDirection)
{
	mAnimDirection = aAnimationDirection;
}

float Sprite::getRotation()
{
	return mRotation;
}

void Sprite::setRotation(float aRotation)
{
	mRotation = aRotation;
}

float Sprite::getScale()
{
	return mScale;
}

void Sprite::setScale(float aScale)
{
	mScale = aScale;
}

D3DCOLOR Sprite::getColor()
{
	return mColor;
}

void Sprite::setColor(const D3DCOLOR& aColor)
{
	mColor = aColor;
}

int Sprite::getMoveTimer()
{
	return mMoveTimer;
}

void Sprite::setMoveTimer(int aMoveTimer)
{
	mMoveTimer = aMoveTimer;
}

bool Sprite::isCollidable()
{
	return mCollidable;
}

void Sprite::setCollidable(bool aCollidable)
{
	mCollidable = aCollidable;
}

CollisionType Sprite::getCollisionMethod()
{
	return mCollisionMethod;
}

void Sprite::setCollisionMethod(CollisionType aCollisionType)
{
	mCollisionMethod = aCollisionType;
}

void Sprite::move()
{
	if (mMoveTimer > 0)
	{
		if (Timer::getTimer() > (static_cast<DWORD>(mMoveStart + mMoveTimer)))
		{
			//reset move timer
			mMoveStart = Timer::getTimer();
			//move sprite by velocity amount
			mPosition.mX += mVelocity.mX;
			mPosition.mY += mVelocity.mY;
		}
	}
	else
	{
		//no movement timer--update at cpu clock speed
		mPosition.mX += mVelocity.mX;
		mPosition.mY += mVelocity.mY;
	}
}

void Sprite::animate()
{
	//update frame based on animdir
	if (mFrameTimer > 0)
	{
		if (Timer::getTimer() > (static_cast<DWORD>(mFrameStart + mFrameTimer)))
		{
			//reset animation timer
			mFrameStart = Timer::getTimer();
			mCurrentFrame += mAnimDirection;

			//keep frame within bounds
			if (mCurrentFrame < 0)
			{
				mCurrentFrame = mTotalFrames - 1;
			}

			if (mCurrentFrame > mTotalFrames - 1)
			{
				mCurrentFrame = 0;
			}
		}
	}
	else
	{
		//no animation timer--update at cpu clock speed
		mCurrentFrame += mAnimDirection;

		if (mCurrentFrame < 0)
		{
			mCurrentFrame = mTotalFrames - 1;
		}

		if (mCurrentFrame > mTotalFrames - 1)
		{
			mCurrentFrame = 0;
		}
	}
}

void Sprite::draw()
{
	//calculate source frame location
	int fx = (mCurrentFrame % mAnimColumns) * mSize.mX;
	int fy = (mCurrentFrame / mAnimColumns) * mSize.mY;
	RECT srcRect = {fx, fy, fx + mSize.mX, fy + mSize.mY};
	transform();
	g_engine->getSpriteHandler()->Draw(mImage->getTexture(), &srcRect, NULL, NULL,
	                                   mColor);
}

Sprite::~Sprite()
{
	if (mImageLoaded)
	{
		delete mImage;
		mImage = NULL;
	}
}

}
