
#include "Rect.h"

namespace Advanced2D
{

template<class T>
Rect<T>::Rect(T aLeft, T aTop, T aRight, T aBottom) :
	mLeft(aLeft),
	mTop(aTop),
	mRight(aRight),
	mBottom(aBottom)
{
}

template<class T>
bool Rect<T>::isInside(T aX, T aY)
{
	return (mLeft < aX && aX < mRight && mTop < aY && aY < mBottom);
}

template<class T>
bool Rect<T>::isInside(T aLeft, T aTop, T aRight, T aBottom, T aX, T aY)
{
	return (aLeft < aX && aX < aRight && aTop < aY && aY < aBottom);
}

}
