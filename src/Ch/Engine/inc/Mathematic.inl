
#include <math.h>

namespace Advanced2D
{

#define M_PI_180 (M_PI / 180)
#define M_180_PI (180.0 / M_PI)
#define M_DOUBLE_PI (2 * M_PI)

template<class T>
T Mathematic<T>::toDegrees(T aRadians)
{
	return aRadians * M_180_PI;
}

template<class T>
T Mathematic<T>::toRadians(T aDegrees)
{
	return aDegrees * M_PI_180;
}

template<class T>
T Mathematic<T>::wrapAngleRadians(T aRadians)
{
	T result = fmod(aRadians, M_DOUBLE_PI);

	if (result < 0)
	{
		result += M_DOUBLE_PI;
	}

	return result;
}

template<class T>
T Mathematic<T>::wrapAngleDegrees(T aDegrees)
{
	T result = fmod(aDegrees, 360.0);

	if (result < 0)
	{
		result += 360.0;
	}

	return result;
}

template<class T>
T Mathematic<T>::linearVelocityX(T aAngle)
{
	aAngle -= 90.0;

	if (aAngle < 0)
	{
		aAngle += 360.0;
	}

	return cos(toRadians(aAngle));
}

template<class T>
T Mathematic<T>::linearVelocityY(T aAngle)
{
	aAngle -= 90.0;

	if (aAngle < 0)
	{
		aAngle += 360.0;
	}

	return sin(toRadians(aAngle));
}

template<class T>
Vector3<T> Mathematic<T>::linearVelocity2d(T aAngle)
{
	return Vector3<T>(linearVelocityX(aAngle), linearVelocityX(aAngle), 0.0);
}

template<class T>
T Mathematic<T>::angleToTarget(T aXsrc, T aYsrc, T aXtrg, T aYtrg)
{
	return atan2(aYtrg - aYsrc, aXtrg - aXsrc);
}

template<class T>
T Mathematic<T>::angleToTarget(const Vector3<T>& aSrc, const Vector3<T>& aTrg)
{
	return atan2(aTrg.mY - aSrc.mY, aTrg.mX - aSrc.mX);
}

}
