#include "CColision.h"

int CColision::RectToRect(TRect& _aRect, TRect& _bRect)
{
	// 교차가 아니면 0반환
	// 걸치면 1반환
	// 포함관계면 2반환
	float fxMin , fyMin;
	float fxMax, fyMax;
	fxMin = _aRect.o_Px < _bRect.o_Px ? _aRect.o_Px : _bRect.o_Px;
	fyMin = _aRect.o_Py < _bRect.o_Py ? _aRect.o_Py : _bRect.o_Py;
	fxMax = _aRect.f_x > _bRect.f_x ? _aRect.f_x : _bRect.f_x;
	fyMax = _aRect.f_y > _bRect.f_y ? _aRect.f_y : _bRect.f_y;
	// 가로판정
	if (_aRect.w + _bRect.w >= fxMax - fxMin)
	{
		// 세로판정
		if (_aRect.h + _bRect.h >= fyMax - fyMin)
		{
			TRect InSideRect;
			float x, y, x2, y2;
			x = _aRect.o_Px > _bRect.o_Px ? _aRect.o_Px : _bRect.o_Px;
			y = _aRect.o_Py > _bRect.o_Py ? _aRect.o_Py : _bRect.o_Py;
			x2 = _aRect.f_x < _bRect.f_x ? _aRect.f_x : _bRect.f_x;
			y2 = _aRect.f_y < _bRect.f_y ? _aRect.f_y : _bRect.f_y;
			InSideRect.Set(x, y, x2 - x, y2 - y);
			if (InSideRect == _aRect || InSideRect == _bRect)
			{
				return CollisionTrigg::RECTINRECT;
			}
			return CollisionTrigg::RECTTORECT;
		}
	}
	return CollisionTrigg::RECTOUT;
}

bool CColision::RectToInRect(TRect& _aRect, TRect& _bRect)
{
	if (_aRect.o_Px <= _bRect.o_Px && _aRect.f_x>=_bRect.f_x)
	{
		if (_aRect.o_Py <= _bRect.o_Py && _aRect.f_y >= _bRect.f_y)
			return true;
	}
	return false;
}

bool CColision::CircleToCircle(Circle& _aRect, Circle& _bRect)
{
	float coliCircle = _aRect.fRadius + _bRect.fRadius;
	float x = fabs(_aRect.cx - _bRect.cx);
	float y = fabs(_aRect.cy - _bRect.cy);
	float fDistance = sqrt(x * x + y * y);
	if (fDistance <= coliCircle)
	{
		// 중심으로부터 거리가 반지름 두개의 길이보다 작으면 충돌
		return true;

	}
	return false;
}
