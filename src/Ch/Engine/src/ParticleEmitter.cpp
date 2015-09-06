
#include "ParticleEmitter.h"
#include "Sprite.h"
#include "Texture.h"

namespace Advanced2D
{

ParticleEmitter::ParticleEmitter() :
	mParticles(),
	mImage(NULL),
	mPosition(),
	mDirection(0.0f),
	mLength(100),
	mMax(100),
	mAlphaMin(254),
	mAlphaMax(255),
	mMinRGB(),
	mMaxRGB(255, 255, 255),
	mSpread(10),
	mVelocity(1.0f),
	mScale(1.0f),
	mImageLoaded(false)

{
}

void ParticleEmitter::setPosition2D(float aX, float aY)
{
	mPosition.mX = aX;
	mPosition.mY = aY;
}

void ParticleEmitter::setPosition2D(const Vector3<float>& aPosition2D)
{
	mPosition = aPosition2D;
}

Vector3<float>& ParticleEmitter::getPosition()
{
	return mPosition;
}

void ParticleEmitter::setDirection(float aDirection)
{
	mDirection = aDirection;
}

float ParticleEmitter::getDirection()
{
	return mDirection;
}

void ParticleEmitter::setMax(int aMax)
{
	mMax = aMax;
}

void ParticleEmitter::setAlphaRange(unsigned char aAlphaMin,
                                    unsigned char aAlphaMax)
{
	mAlphaMin = aAlphaMin;
	mAlphaMax = aAlphaMax;
}

void ParticleEmitter::setColorRange(unsigned char aR1, unsigned char aG1,
                                    unsigned char aB1, unsigned char aR2, unsigned char aG2,
                                    unsigned char aB2)
{
	mMinRGB.mX = aR1;
	mMinRGB.mY = aG1;
	mMinRGB.mZ = aB1;
	mMaxRGB.mX = aR2;
	mMaxRGB.mY = aG2;
	mMaxRGB.mZ = aB2;
}


void ParticleEmitter::setSpread(int aSpread)
{
	mSpread = aSpread;
}

void ParticleEmitter::setLength(float aLength)
{
	mLength = aLength;
}

void ParticleEmitter::setVelocity(float aVelocity)
{
	mVelocity = aVelocity;
}

void ParticleEmitter::setScale(float aScale)
{
	mScale = aScale;
}

bool ParticleEmitter::loadImage(const _TCHAR* aFileName)
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
		mImage = new Texture(aFileName, D3DCOLOR_XRGB(0, 0, 0));
		mImageLoaded = true;
	}
	catch (const std::exception&)
	{
		mImageLoaded = false;
	}

	if (mImageLoaded)
	{
		return true;
	}

	return false;
}

void ParticleEmitter::draw()
{
	for (iter i = mParticles.begin(); i != mParticles.end(); ++i)
	{
		(*i)->draw();
	}
}

void ParticleEmitter::update()
{
	static Timer tmr;

	//do we nead to add a new particles? && trivial but necessary slowdown
	if ((static_cast<int>(mParticles.size()) < mMax) && tmr.stopwatch(1))
	{
		add();
	}

	for (iter i = mParticles.begin(); i != mParticles.end(); ++i)
	{
		//update the particle's position
		(*i)->move();

		//is particle beyond the emitter's range?
		if ((*i)->getPosition().distance2D(mPosition) > mLength)
		{
			(*i)->setPosition2D(mPosition);
		}
	}
}

void ParticleEmitter::add()
{
	static const float M_PI_180 = static_cast<float>(M_PI / 180.0f);
	//create a new particle
	Sprite* p = new Sprite();
	p->setImage(mImage);
	p->setPosition2D(mPosition);
	//add some randomness to the spread
	float variation = (static_cast<float>(rand() % mSpread) - static_cast<float>
	                   (mSpread) / 2.0f) / 100.0f;
	//set linear velocity
	float dirParticle = M_PI_180 * (mDirection - 90.0f);
	p->setVelocity((cos(dirParticle) + variation) * mVelocity,
	               (sin(dirParticle) + variation) * mVelocity);
	//set random color based on ranges
	unsigned char r = static_cast<unsigned char>(rand() % (mMaxRGB.mX - mMinRGB.mX)
	                  + mMinRGB.mX);
	unsigned char g = static_cast<unsigned char>(rand() % (mMaxRGB.mY - mMinRGB.mY)
	                  + mMinRGB.mY);
	unsigned char b = static_cast<unsigned char>(rand() % (mMaxRGB.mZ - mMinRGB.mZ)
	                  + mMinRGB.mZ);
	unsigned char a = static_cast<unsigned char>(rand() % (mAlphaMax - mAlphaMin) +
	                  mAlphaMin);
	p->setColor(D3DCOLOR_RGBA(r, g, b, a));
	//set the scale
	p->setScale(mScale);
	//add particle to the emitter
	mParticles.push_back(p);
}

ParticleEmitter::~ParticleEmitter()
{
	delete mImage;

	for (iter i = mParticles.begin(); i != mParticles.end(); ++i)
	{
		delete (*i);
	}

	mParticles.clear();
}

}
