#ifndef __PARTICLE_EMITTER_H_
#define __PARTICLE_EMITTER_H_

#include "Vector3.h"
#include <tchar.h>
#include <vector>

namespace Advanced2D
{
class Sprite;
class Texture;
class ParticleEmitter
{
private:
	typedef std::vector<Sprite*>::iterator iter;
	std::vector<Sprite*> mParticles;
	Texture* mImage;
	Vector3<float> mPosition;
	float mDirection;
	float mLength;
	int mMax;
	unsigned char mAlphaMin;
	unsigned char mAlphaMax;
	Vector3<unsigned char> mMinRGB;
	Vector3<unsigned char> mMaxRGB;
	int mSpread;
	float mVelocity;
	float mScale;
	bool mImageLoaded;
public:
	ParticleEmitter();

	void setPosition2D(float aX, float aY);
	void setPosition2D(const Vector3<float>& aPosition2D);
	Vector3<float>& getPosition();
	void setDirection(float aDirection);
	float getDirection();
	void setMax(int aMax);
	void setAlphaRange(unsigned char aAlphaMin, unsigned char aAlphaMax);
	void setColorRange(unsigned char aR1, unsigned char aG1, unsigned char aB1,
	                   unsigned char aR2, unsigned char aG2, unsigned char aB2);
	void setSpread(int aSpread);
	void setLength(float aLength);
	void setVelocity(float aVelocity);
	void setScale(float aScale);
	bool loadImage(const _TCHAR* aFileName);
	void draw();
	void update();
	void add();

	virtual ~ParticleEmitter();
};
}

#endif
