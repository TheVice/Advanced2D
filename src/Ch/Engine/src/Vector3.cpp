
#include "Vector3.h"
#include <float.h>

namespace Advanced2D
{

bool Vector3<bool>::operator == (const Vector3<bool>& aVector3) const
{
	return ((aVector3.mX == mX) &&
	        (aVector3.mY == mY) &&
	        (aVector3.mZ == mZ));
}

bool Vector3<char>::operator == (const Vector3<char>& aVector3) const
{
	return ((aVector3.mX == mX) &&
	        (aVector3.mY == mY) &&
	        (aVector3.mZ == mZ));
}

bool Vector3<int>::operator == (const Vector3<int>& aVector3) const
{
	return ((aVector3.mX == mX) &&
	        (aVector3.mY == mY) &&
	        (aVector3.mZ == mZ));
}

bool Vector3<long>::operator == (const Vector3<long>& aVector3) const
{
	return ((aVector3.mX == mX) &&
	        (aVector3.mY == mY) &&
	        (aVector3.mZ == mZ));
}

bool Vector3<float>::operator == (const Vector3<float>& aVector3) const
{
	return (
	           ((aVector3.mX - 50 * FLT_EPSILON) < mX) &&
	           (mX < (50 * FLT_EPSILON + aVector3.mX)) &&
	           ((aVector3.mY - 50 * FLT_EPSILON) < mY) &&
	           (mY < (50 * FLT_EPSILON + aVector3.mY)) &&
	           ((aVector3.mZ - 50 * FLT_EPSILON) < mZ) &&
	           (mZ < (50 * FLT_EPSILON + aVector3.mZ)) );
}

bool Vector3<double>::operator == (const Vector3<double>& aVector3) const
{
	return (
	           ((aVector3.mX - 100 * DBL_EPSILON) < mX) &&
	           (mX < (100 * DBL_EPSILON + aVector3.mX)) &&
	           ((aVector3.mY - 100 * DBL_EPSILON) < mY) &&
	           (mY < (100 * DBL_EPSILON + aVector3.mY)) &&
	           ((aVector3.mZ - 100 * DBL_EPSILON) < mZ) &&
	           (mZ < (100 * DBL_EPSILON + aVector3.mZ)) );
}

}
