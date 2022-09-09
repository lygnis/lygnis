#pragma once
class Point2D
{
public:
	float m_x;
	float m_y;
public:
	Point2D();
	Point2D(float _x, float _y);
	~Point2D() {}
public:
	Point2D operator + (Point2D& _point);
	Point2D operator - (Point2D& _point);
	Point2D operator * (float _scalar);
	Point2D operator / (float _scalar);

public:
	float PointBetweenPoint(Point2D& _P2);
};

