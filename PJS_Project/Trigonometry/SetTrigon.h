#pragma once
#include <math.h>
#define Pi 3.141592
#define DegreeToRad Pi/180
#define RadToDegree 180/Pi
class SetTrigon
{

public:
	float m_fWidth;
	float m_fHeight;
	float m_fLaw;
	float m_fAngle;
public:
	SetTrigon();
	SetTrigon(float _width, float _height);
	~SetTrigon() {};
public:
	float GetLenght(float _width, float _height);
	float GetAngle(float _width, float _height);
	SetTrigon GetLenCosSinAngle(float _angle);
};

