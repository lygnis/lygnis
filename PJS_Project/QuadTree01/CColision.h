#pragma once
#include <math.h>
enum CollisionTrigg
{
	RECTOUT = 0,
	RECTTORECT,
	RECTINRECT
};
struct Circle
{
	float cx;
	float cy;
	float fRadius;
	Circle() {};
	Circle(float x, float y , float r)
	{
		cx = x;
		cy = y;
		fRadius = r;
	}
};
struct Rect
{
	float o_Px;
	float o_Py;
	float w;
	float h;
};
struct TRect : Rect
{
public:
	float f_x;
	float f_y;

public:
	bool operator == (TRect& obj)			// 크기가 같을때
	{
		if (fabs(o_Px - obj.o_Px) < 0.0001f)
		{
			if (fabs(o_Py - obj.o_Py) < 0.0001f)
			{
				if (fabs(w - obj.w) < 0.0001f)
				{
					if (fabs(h - obj.h) < 0.0001f)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
	void Set(float x, float y, float w, float h)
	{
		this->o_Px = x;
		this->o_Py = y;
		this->w = w;
		this->h = h;
		f_x = x + w;
		f_y = y + h;
	}
	TRect(float x, float y, float w, float h)
	{
		Set(x, y, w, h);
	}
	TRect()
	{}
	~TRect() {}
};





class CColision
{
public:
	static int RectToRect(TRect& _aRect, TRect& _bRect);
	static bool RectToInRect(TRect& _aRect, TRect& _bRect);
	static bool CircleToCircle(Circle& _aRect, Circle& _bRect);
};

