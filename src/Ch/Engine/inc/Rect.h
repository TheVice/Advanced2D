#ifndef __RECT_H_
#define __RECT_H_

namespace Advanced2D
{
template<class T>
struct Rect
{
	T mLeft;
	T mTop;
	T mRight;
	T mBottom;
	Rect(T aLeft, T aTop, T aRight, T aBottom);
	bool isInside(T aX, T aY);
	static bool isInside(T aLeft, T aTop, T aRight, T aBottom, T aX, T aY);
};
}

#include "Rect.inl"

#endif
