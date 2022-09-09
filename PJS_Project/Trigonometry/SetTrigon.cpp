#include "SetTrigon.h"

SetTrigon::SetTrigon()
{
	m_fWidth = 0;
	m_fHeight = 0;
	m_fLaw = 0;
}

SetTrigon::SetTrigon(float _width, float _height)
{
	m_fWidth = _width;
	m_fHeight = _height;
	m_fLaw = GetLenght(_width, _height);
	m_fAngle = GetAngle(_width, _height);
}

float SetTrigon::GetLenght(float _width, float _height)
{
	float temp = sqrt(_width * _width + _height * _height);
	return temp;
}

float SetTrigon::GetAngle(float _width, float _height)
{
	float angle = atan((_height / _width));
	angle *= RadToDegree;
	return angle;
}

SetTrigon SetTrigon::GetLenCosSinAngle(float _angle)
{
	return SetTrigon(m_fLaw*cos(_angle), m_fLaw*sin(_angle));
}
 