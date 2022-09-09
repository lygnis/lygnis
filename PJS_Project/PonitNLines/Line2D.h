#pragma once
#include "Point2D.h"
#include <math.h>
class Line2D
{
public:
	Point2D m_P1;
	Point2D m_P2;
	float m_Slope;
	float m_Distance;
public:
	Line2D() {};
	Line2D(Point2D& _p1, Point2D& _p2);
	~Line2D() {};
public:
	// 직교하는지 안하는지
	bool arePrep(Line2D& _p1, Line2D& _p2);
	Point2D CrossLineToPoint(Line2D& _l1, Line2D& _l2);
	bool CheckToCross(Line2D& _l1, Line2D& l2);
};

