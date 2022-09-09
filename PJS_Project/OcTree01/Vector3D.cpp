#include "Vector3D.h"

Vector3D Vector3D::operator+(Vector3D& _vec)
{
	return Vector3D(x + _vec.x, y + _vec.y, z + _vec.z);
}

Vector3D Vector3D::operator/(float _fScalar)
{
	return Vector3D(x / _fScalar, y / _fScalar, z / _fScalar);
}

Vector3D Vector3D::operator-(Vector3D& _vec)
{
	return Vector3D(x - _vec.x, y - _vec.y, z - _vec.z);
}
Vector3D Vector3D::operator+=(Vector3D& _vec)
{
	return Vector3D(this->x+_vec.x, this->y + _vec.y, this->z + _vec.z);
}
Vector3D Vector3D::operator*(float _scalar)
{
	return Vector3D(this->x* _scalar, this->y* _scalar, this->z*_scalar);
}
bool Vector3D::operator==(Vector3D& _vec)
{
	if (fabs(x - _vec.x) < EPSILON
		&& fabs(y - _vec.y) < EPSILON
		&& fabs(z - _vec.z) < EPSILON)
	{
		return true;
	}
	return false;
}
Vector3D::Vector3D()
{
	x = 0;
	y = 0; 
	z = 0;
}

Vector3D::Vector3D(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}

Vector3D::Vector3D(const Vector3D& _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
}

Vector3D Vector3D::Nomalized()
{
	Vector3D _NormalVec = *this;
	float _length = Length();
	_NormalVec.x = x / _length;
	_NormalVec.y = y / _length;
	_NormalVec.z = z / _length;
	return _NormalVec;
}

float Vector3D::Length()
{
	
	return sqrt(x*x + y*y + z*z);
}
