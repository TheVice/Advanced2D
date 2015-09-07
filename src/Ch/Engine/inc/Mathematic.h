#ifndef __MATH_H_
#define __MATH_H_

#include "Vector3.h"

namespace Advanced2D
{
template<class T>
class Mathematic
{
public:
	static T toDegrees(T aRadians);
	static T toRadians(T aDegrees);
	static T wrapAngleRadians(T aRadians);
	static T wrapAngleDegrees(T aDegrees);
	static T linearVelocityX(T aAngle);
	static T linearVelocityY(T aAngle);
	static Vector3<T> linearVelocity2d(T aAngle);
	static T angleToTarget(T aXsrc, T aYsrc, T aXtrg, T aYtrg);
	static T angleToTarget(const Vector3<T>& aSrc, const Vector3<T>& aTrg);
};
}

#include "Mathematic.inl"

#endif
