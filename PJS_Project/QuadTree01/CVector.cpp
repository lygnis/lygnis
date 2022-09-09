#include "CVector.h"

CVector::CVector()
{
	x = 0.0f;
	y = 0.0f;
}

CVector::CVector(float x, float y)
{
	v[0] = x;
	v[1] = y;
}

CVector::CVector(const CVector& _vector)
{
	x = _vector.x;
	y = _vector.y;
}

CVector CVector::operator+(CVector& _vector)
{
	return CVector(x+_vector.x,y+_vector.y);
}

CVector CVector::operator-(CVector& _vector)
{
	return CVector(x-_vector.x, y-_vector.y);
}

CVector CVector::operator*(float _scalar)
{
	return CVector(x*_scalar, y*_scalar);
}

CVector CVector::operator+=(CVector& _vector)
{
	this->x = this->x + _vector.x;
	this->y = this->y + _vector.y;
	return *this;
}

CVector CVector::operator/(float _scalar)
{
	return CVector(x/_scalar, y/_scalar);
}

CVector CVector::operator*=(float _scalar)
{
	this->x = this->x * _scalar;
	this->y = this->y * _scalar;
	return *this;
}

bool CVector::operator==(CVector& _vector)
{
	if (fabs(x - _vector.x) < EPSILON)
	{
		if (fabs(y - _vector.y) < EPSILON)
			return true;
	}
	return false;
}

float CVector::PrevLength()
{
	return (x * x + y * y);
}

float CVector::Length()
{
	return sqrt(PrevLength());
}

CVector CVector::Nomalized()
{
	CVector _NomalVec = *this;
	float fInverse = 1.0f / Length();
	_NomalVec.x = _NomalVec.x * fInverse;
	_NomalVec.y = _NomalVec.x * fInverse;
	return _NomalVec;
}

float CVector::Angle(CVector& _vec)
{
	float fcos = x * _vec.x + y * _vec.y;
	fcos = fcos / Length()*_vec.Length();
	float fRadian = acos(fcos);
	float fDgree = RadianToDgree(fRadian);

	return fDgree;
}
