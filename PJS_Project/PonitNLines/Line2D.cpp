#include "Line2D.h"
Line2D::Line2D(Point2D& _p1, Point2D& _p2)
{
	m_P1 = _p1;
	m_P2 = _p2;
	// 기울기 : y2 - y1 / x2 - x1
	m_Slope = (_p2.m_y - _p1.m_y) / (_p2.m_x - _p1.m_x);
	float _tempx = _p2.m_x - _p1.m_x;
	float _tempy = _p2.m_y - _p1.m_y;
	m_Distance = sqrt(_tempx * _tempx + _tempy * _tempy);
}

bool Line2D::arePrep(Line2D& _p1, Line2D& _p2)
{
	// 기울기 둘을 곱했을때 -1이면 직교한다.
	if (fabs((_p1.m_Slope * _p2.m_Slope) + 1.0f) < 0.00001f)
		return true;

	return false;
}

Point2D Line2D::CrossLineToPoint(Line2D& _l1, Line2D& _l2)
{
	bool bln = CheckToCross(_l1, _l2);
	if (bln == true)
	{
		Point2D temp;
		temp.m_x = (_l1.m_Slope * _l1.m_P1.m_x - _l2.m_Slope * _l2.m_P2.m_x + _l2.m_P2.m_y - _l1.m_P1.m_y) / (_l1.m_Slope - _l2.m_Slope);
		temp.m_y = (_l1.m_Slope * (temp.m_x - _l1.m_P1.m_x) + _l1.m_P1.m_y);
		return temp;
	}
}

bool Line2D::CheckToCross(Line2D& _l1, Line2D& l2)
{
	if (_l1.m_Slope != l2.m_Slope)
		return true;

	return false;
}




