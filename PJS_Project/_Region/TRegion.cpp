#include "TRegion.h"

TRegion TRegion::operator++(int)			// 후위 연산
{
	TRegion temp = *this;
	++x, ++y;
	return temp;
}

TRegion TRegion::operator++(void)
{
	++x, ++y;
	return *this;
}

TRegion TRegion::operator+(TRegion& _i)
{
	TRegion temp;
	temp.x = x + _i.x;
	temp.y = y + _i.y;
	return temp;
}

TRegion TRegion::operator-(const TRegion &pt) const
{
	TRegion temp;
	temp.x = x - pt.x;
	temp.y = y - pt.y;
	return temp;
}

TRegion& TRegion::operator=(const TRegion& pt)
{
	x = pt.x; y = pt.y;
	return *this;
}

TRegion::TRegion(int x, int y)
{
	this->x = x; this->y = y;
}
TRegion::TRegion(void)
{

}
TRegion::~TRegion()
{

}

TRegion operator+(int pl, TRegion& pt)
{
	TRegion temp;
	temp.x = pl + pt.x;
	temp.y = pl + pt.y;
	return temp;
}
