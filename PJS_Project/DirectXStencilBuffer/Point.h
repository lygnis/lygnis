#pragma once
class Point
{
public:
	Point() : _x(0), _y(0)
	{}
	Point(int x, int y) : _x(x), _y(y)
	{}
	Point(const Point& point) : _x(point._x), _y(point._y)
	{}
	~Point()
	{}
public:
	int _x = 0;
	int _y = 0;
};