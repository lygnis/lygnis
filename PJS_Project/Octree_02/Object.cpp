#include "Object.h"

void Object::SetPosition(Vector3D _ctPoint, Vector3D _size)
{
	m_Coor.SetPosition(_ctPoint, _size);
}

void Object::Frame(float _fDeltaTime, float fGameTime)
{
}

void Object::AddForce(Vector3D _dir)
{
	m_vForce = m_vForce +_dir;
}

Object::Object()
{
	Vector3D vPos, vSize;
	vPos.x = 20 + (rand() % 80);
	vPos.y = 20 + (rand() % 80);
	vPos.z = 20 + (rand() % 80);
	vSize.x = 5.0f + (rand() % 5);
	vSize.y = 5.0f + (rand() % 5);
	vSize.z = 5.0f + (rand() % 5);
	m_Coor.SetPosition(vPos, vSize);
	m_vDirection.x = cos(rand());
	m_vDirection.y = sin(rand());
	m_vDirection.z = cos(rand());
	m_vDirection.Nomalized();
	m_fFriction = 1.0f;
	m_mMass = 100.0f;
	m_fSpeed = 10.0f;
}

