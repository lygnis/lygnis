#include "Point2D.h"

Point2D::Point2D()
{
	m_x = 0;
	m_y = 0;
}

Point2D::Point2D(float _x, float _y)
{
	m_x = _x;
	m_y = _y;
}

Point2D Point2D::operator+(Point2D& _point)
{
	return Point2D(m_x + _point.m_x, m_y + _point.m_y);
}

Point2D Point2D::operator-(Point2D& _point)
{
	return Point2D(m_x - _point.m_x, m_y-_point.m_y);
}

Point2D Point2D::operator*(float _scalar)
{
	return Point2D(this->m_x*_scalar, this->m_y*_scalar);
}

Point2D Point2D::operator/(float _scalar)
{
	return Point2D(this->m_x / _scalar, this->m_y / _scalar);
}


