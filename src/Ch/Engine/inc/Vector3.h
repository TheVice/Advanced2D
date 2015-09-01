#ifndef __VECTOR3_H_
#define __VECTOR3_H_

namespace Advanced2D
{
template<class T>
class Vector3
{
public:
	T mX, mY, mZ;
	Vector3();
	Vector3(const Vector3& aVector3);
	Vector3(T aX, T aY, T aZ);
	void move(T aDeltaX, T aDeltaY, T aDeltaZ);
	void operator += (const Vector3& aVector3);
	void operator -= (const Vector3& aVector3);
	void operator *= (const Vector3& aVector3);
	void operator /= (const Vector3& aVector3);
	bool operator == (const Vector3& aVector3) const;
	bool operator != (const Vector3& aVector3) const;
	Vector3<T>& operator = (const Vector3& aVector3);
	T distance2D(const Vector3& aVector3);
	T length() const;
	T dotProduct(const Vector3& aVector3);
	Vector3<T> crossProduct(const Vector3& aVector3) const;
	Vector3<T> normal() const;
	virtual ~Vector3();
};
}

#include "Vector3.inl"

#endif
