
#include "Entity.h"

namespace Advanced2D
{

int Entity::sId = 0;

Entity::Entity(enum RenderType aRenderType) :
	mId(sId++),
	mRenderType(aRenderType),
	mName(),
	mObjectType(0),
	mVisible(true),
	mAlive(true),
	mLifeTimeLength(0),
	mLifeTimeTimer()
{
}

int Entity::getID()
{
	return mId;
}

enum RenderType Entity::getRenderType()
{
	return mRenderType;
}

_TCHAR* Entity::getName()
{
	return mName;
}

void Entity::setName(const _TCHAR* aName)
{
#if _MSC_VER > 1310
	_tcsncpy_s(mName, MAX_PATH, aName,
	           sizeof(mName) / sizeof(*mName));
#else
	_tcsncpy(mName, aName, sizeof(mName) / sizeof(*mName));
#endif
}

int Entity::getObjectType()
{
	return mObjectType;
}

void Entity::setObjectType(int aObjectType)
{
	mObjectType = aObjectType;
}

bool Entity::isVisible()
{
	return mVisible;
}

void Entity::setVisible(bool aVisible)
{
	mVisible = aVisible;
}

bool Entity::isAlive()
{
	return mAlive;
}

void Entity::setAlive(bool aAlive)
{
	mAlive = aAlive;
}

int Entity::getLifeTime()
{
	return mLifeTimeLength;
}

void Entity::setLifeTime(int aLifeTime)
{
	mLifeTimeLength = aLifeTime;
}

bool Entity::isLifeTimeExpired()
{
	return mLifeTimeTimer.stopwatch(mLifeTimeLength);
}

Entity::~Entity()
{
}

}
