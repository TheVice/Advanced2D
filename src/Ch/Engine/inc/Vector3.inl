
#include <cmath>

namespace Advanced2D
{

template<class T>
Vector3<T>::Vector3() : mX(0), mY(0), mZ(0)
{
}

template<class T>
Vector3<T>::Vector3(const Vector3<T>& aVector3)
{
	*this = aVector3;
}

template<class T>
Vector3<T>::Vector3(T aX, T aY, T aZ) : mX(aX), mY(aY), mZ(aZ)
{
}

template<class T>
void Vector3<T>::move(T aDeltaX, T aDeltaY, T aDeltaZ)
{
	mX += aDeltaX;
	mY += aDeltaY;
	mZ += aDeltaZ;
}

template<class T>
void Vector3<T>::operator += (const Vector3<T>& aVector3)
{
	move(aVector3.mX, aVector3.mY, aVector3.mZ);
}

template<class T>
void Vector3<T>::operator -= (const Vector3<T>& aVector3)
{
	move(-1 * aVector3.mX, -1 * aVector3.mY, -1 * aVector3.mZ);
}

template<class T>
void Vector3<T>::operator *= (const Vector3<T>& aVector3)
{
	mX = mX * aVector3.mX;
	mY = mY * aVector3.mY;
	mZ = mZ * aVector3.mZ;
}

template<class T>
void Vector3<T>::operator /= (const Vector3<T>& aVector3)
{
	mX = mX / aVector3.mX;
	mY = mY / aVector3.mY;
	mZ = mZ / aVector3.mZ;
}

template<class T>
bool Vector3<T>::operator != (const Vector3<T>& aVector3) const
{
	return (!(*this == aVector3));
}

template<class T>
Vector3<T>& Vector3<T>::operator = (const Vector3<T>& aVector3)
{
	mX = aVector3.mX;
	mY = aVector3.mY;
	mZ = aVector3.mZ;
	return *this;
}

template<class T>
T Vector3<T>::distance2D(const Vector3<T>& aVector3)
{
	return sqrt(pow((aVector3.mX - mX), 2) + pow((aVector3.mY - mY), 2));
}

template<class T>
T Vector3<T>::length() const
{
	return sqrt(pow(mX, 2) + pow(mY, 2) + pow(mZ, 2));
}

template<class T>
T Vector3<T>::dotProduct(const Vector3<T>& aVector3)
{
	return (aVector3.mX * mX + aVector3.mY * mY + aVector3.mZ * mZ);
}

template<class T>
Vector3<T> Vector3<T>::crossProduct(const Vector3<T>& aVector3) const
{
	return Vector3<T>(mY * aVector3.mZ - mZ * aVector3.mY,
	                  mZ * aVector3.mY - mX * aVector3.mZ,
	                  mX * aVector3.mY - mY * aVector3.mX);
}

template<class T>
Vector3<T> Vector3<T>::normal() const
{
	T l = length();

	if (l > 0)
	{
		l = 1 / l;
	}

	return Vector3<T>(mX * l, mY * l, mZ * l);
}

template<class T>
Vector3<T>::~Vector3()
{
}

}
