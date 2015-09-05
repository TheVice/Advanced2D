#ifndef __ENTITY_H_
#define __ENTITY_H_

#include "Timer.h"
#include <tchar.h>

namespace Advanced2D
{
enum RenderType
{
	RENDER2D = 0,
	RENDER3D = 1
};

class Entity
{
private:
	static int sId;
	int mId;
	enum RenderType mRenderType;
	_TCHAR mName[MAX_PATH];
	int mObjectType;
	bool mVisible;
	bool mAlive;
	int mLifeTimeLength;
	Timer mLifeTimeTimer;

	Entity();
	Entity(const Entity& aRhs);
	Entity& operator=(const Entity& aRhs);
public:
	Entity(enum RenderType aRenderType);
	int getID();
	enum RenderType getRenderType();
	_TCHAR* getName();
	void setName(const _TCHAR* aName);
	int getObjectType();
	void setObjectType(int aObjectType);
	bool isVisible();
	void setVisible(bool aVisible);
	bool isAlive();
	void setAlive(bool aAlive);
	int getLifeTime();
	void setLifeTime(int aLifeTime);
	bool isLifeTimeExpired();
	virtual void move() = 0;
	virtual void animate() = 0;
	virtual void draw() = 0;
	virtual ~Entity();
};
}

#endif
