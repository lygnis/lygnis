#include "Vector3D.h"
Vector3D::Vector3D()
{

}
Vector3D::Vector3D(float _x, float _y, float _z)
{
	v[0] = _x;
	v[1] = _y;
	v[2] = _z;
	m_fLength = GetLength(_x,  _y,  _z);
	//m_fAngle = GetAngle(_x, _y);
}


float Vector3D::GetLength(float _x, float _y, float _z)
{
	return sqrt(_x*_x+_y* _y + _z* _z);
}
Vector3D Vector3D::Nomalized(Vector3D& _vec)
{
	return Vector3D(x/m_fLength, y/m_fLength, z/m_fLength);
}
float Vector3D::DotVector(const Vector3D& _vec)
{
	return x * _vec.x + y * _vec.y + z * _vec.z;
}
Vector3D Vector3D::OuterProduct(const Vector3D& _vec)
{
	// 2 3 - 3 2, 3 1 - 1 3 , 1 2, 2 1
	Vector3D temp;
	temp.x = (y * _vec.z) - (z * _vec.y);
	temp.y = (z * _vec.x) - (x * _vec.z);
	temp.z = (x * _vec.y) - (y * _vec.x);
	return temp;
}
float Vector3D::BetweenAngelVec(const Vector3D& _vec)
{
	Vector3D outerPro = this->OuterProduct(_vec);
	outerPro.m_fLength = outerPro.GetLength(outerPro.x, outerPro.y, outerPro.z);
	float temp = sqrt(outerPro.m_fLength) / sqrt(this->m_fLength * _vec.m_fLength);
	temp = asin(temp) * RadToDegree;
	return temp;
}
//float Vector3D::GetAngle(float _x, float _y)
//{
//	float angle = atan(_y / _x);
//	angle *= RadToDegree;
//	return angle;
//}
Vector3D Vector3D::operator+ (Vector3D& _vec)
{
	return Vector3D(x + _vec.x, y + _vec.y, z + _vec.z);
}
Vector3D Vector3D::operator*(float _scalar)
{
	return Vector3D(this->x * _scalar, this->y * _scalar, this->z * _scalar);
}
Vector3D Vector3D::operator-(Vector3D& _vec)
{
	return Vector3D(x - _vec.x, y - _vec.y, z - _vec.z);
}