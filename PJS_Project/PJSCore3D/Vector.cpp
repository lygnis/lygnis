#include "Vector.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(float x, float y)
{
	v[0] = x;
	v[1] = y;
}


Vector2D::Vector2D(const Vector2D& _vec)
{
	x = _vec.x;
	y = _vec.y;
}

Vector2D Vector2D::operator+(Vector2D& _vec)
{
	return Vector2D(x+_vec.x, y+_vec.y);
}

Vector2D Vector2D::operator-(Vector2D& _vec)
{
	return Vector2D(x-_vec.x, y-_vec.y);
}

Vector2D Vector2D::operator*(float _scala)
{
	return Vector2D(x*_scala, y*_scala);
}

Vector2D Vector2D::operator/(float _scala)
{
	return Vector2D(x/_scala, y/_scala);
}

Vector2D Vector2D::operator*=(float _scala)
{
	x *= _scala;
	y*=_scala;
	return *this;
}

Vector2D Vector2D::operator+=(Vector2D& _vec)
{
	x += _vec.x;
	y += _vec.y;
	return *this;
}

Vector2D Vector2D::operator-=(Vector2D& _vec)
{
	x -= _vec.x;
	y -= _vec.y;

	return *this;
}

bool Vector2D::operator==(Vector2D& _vec)
{
	if (fabs(x - _vec.x) < 0.0001 && fabs(y - _vec.y) < 0.0001)
	{
		true;
	}
	return false;
}

bool Vector2D::operator<=(Vector2D& _vec)
{
	if (x <= _vec.x && y <= _vec.y)
	{
		return true;
	}
	return false;
}

bool Vector2D::operator>=(Vector2D& _vec)
{
	if (x >= _vec.x && y >= _vec.y)
	{
		return true;
	}
	return false;
}

float Vector2D::Length()
{
	return sqrt(x * x + y * y);
}

Vector2D Vector2D::Normalized()
{
	Vector2D temp;
	float _ftemp = 1 / Length();
	temp.x = x* _ftemp;
	temp.y = y * _ftemp;

	return temp;
}

float Vector2D::Angle(Vector2D& _vec)
{
	float temp = x * _vec.x + y * _vec.y;
	float fRadian = acos(temp /( this->Length() * _vec.Length()));
	float fDegree = RadToDegree(fRadian);
	return fDegree;
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

Vector3D Vector3D::operator+(Vector3D& _vec)
{
	return Vector3D(x + _vec.x, y + _vec.y, z + _vec.z);
}

Vector3D Vector3D::operator-(Vector3D& _vec)
{
	return Vector3D(x - _vec.x, y - _vec.y, z - _vec.z);
}

Vector3D Vector3D::operator*(float _scala)
{
	return Vector3D(x * _scala, y * _scala, z * _scala);
}

Vector3D Vector3D::operator/(float _scala)
{
	return Vector3D(x / _scala, y / _scala, z / _scala);
}

Vector3D Vector3D::operator*=(float _scala)
{
	x *= _scala;
	y *= _scala;
	z *= _scala;
	return *this;
}

Vector3D Vector3D::operator+=(Vector3D& _vec)
{
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;
	return *this;
}

Vector3D Vector3D::operator-=(Vector3D& _vec)
{
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;

	return *this;
}

bool Vector3D::operator==(Vector3D& _vec)
{
	if (fabs(x - _vec.x) < 0.0001 && fabs(y - _vec.y) < 0.0001 && fabs(z - _vec.z) < 0.0001)
	{
		true;
	}
	return false;
}

bool Vector3D::operator<=(Vector3D& _vec)
{
	if (x <= _vec.x && y <= _vec.y&& z <= _vec.z)
	{
		return true;
	}
	return false;
}

bool Vector3D::operator>=(Vector3D& _vec)
{
	if (x >= _vec.x && y >= _vec.y&& z >= _vec.z)
	{
		return true;
	}
	return false;
}

float Vector3D::Length()
{
	return sqrt(x * x + y * y + z*z);
}

Vector3D Vector3D::Normalized()
{
	Vector3D temp;
	float _ftemp = 1 / Length();
	temp.x = x * _ftemp;
	temp.y = y * _ftemp;
	temp.z = z * _ftemp;

	return temp;
}

float Vector3D::Angle(Vector3D& _vec)
{
	float temp = x * _vec.x + y * _vec.y + z * _vec.z;
	float fRadian = acos(temp / (this->Length() * _vec.Length()));
	float fDegree = RadToDegree(fRadian);
	return fDegree;
}

Vector4D::Vector4D()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
	v[3] = w;
}

Vector4D::Vector4D(const Vector4D& _vec)
{
	x = _vec.x;
	y = _vec.y;
	z = _vec.z;
	w = _vec.w;
}

Vector4D Vector4D::operator+(Vector4D& _vec)
{
	return Vector4D(x + _vec.x, y + _vec.y, z + _vec.z, w + _vec.w);
}

Vector4D Vector4D::operator-(Vector4D& _vec)
{
	return Vector4D(x - _vec.x, y - _vec.y, z - _vec.z, w - _vec.w);
}

Vector4D Vector4D::operator*(float _scala)
{
	return Vector4D(x * _scala, y * _scala, z * _scala, w * _scala);
}

Vector4D Vector4D::operator/(float _scala)
{
	return Vector4D(x / _scala, y / _scala, z / _scala, w / _scala);
}

Vector4D Vector4D::operator*=(float _scala)
{
	x *= _scala;
	y *= _scala;
	z *= _scala;
	w *= _scala;
	return *this;
}

Vector4D Vector4D::operator+=(Vector4D& _vec)
{
	x += _vec.x;
	y += _vec.y;
	z += _vec.z;
	w += _vec.w;
	return *this;
}

Vector4D Vector4D::operator-=(Vector4D& _vec)
{
	x -= _vec.x;
	y -= _vec.y;
	z -= _vec.z;
	w -= _vec.w;
	return *this;
}

bool Vector4D::operator==(Vector4D& _vec)
{
	if (fabs(x - _vec.x) < 0.0001 && fabs(y - _vec.y) < 0.0001 && fabs(z - _vec.z) < 0.0001 && fabs(w - _vec.w) < 0.0001)
	{
		true;
	}
	return false;
}

bool Vector4D::operator<=(Vector4D& _vec)
{
	if (x <= _vec.x && y <= _vec.y && z <= _vec.z && z <= _vec.z)
	{
		return true;
	}
	return false;
}

bool Vector4D::operator>=(Vector4D& _vec)
{
	if (x >= _vec.x && y >= _vec.y && z >= _vec.z&& w >= _vec.w)
	{
		return true;
	}
	return false;
}

float Vector4D::Length()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Vector4D Vector4D::Normalized()
{
	Vector4D temp;
	float _ftemp = 1 / Length();
	temp.x = x * _ftemp;
	temp.y = y * _ftemp;
	temp.z = z * _ftemp;
	temp.w = w * _ftemp;
	return temp;
}

float Vector4D::Angle(Vector4D& _vec)
{
	float temp = x * _vec.x + y * _vec.y + z * _vec.z + w* _vec.w;
	float fRadian = acos(temp / (this->Length() * _vec.Length()));
	float fDegree = RadToDegree(fRadian);
	return fDegree;
}

