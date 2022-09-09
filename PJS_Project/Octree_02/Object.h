#pragma once
#include "Vector3D.h"
#include "Coordinate.h"
#include <math.h>
#include <iostream>
// ������Ʈ�� �����־�� �� ������
// ����, ���ӵ�, �ӵ�, ������, ��, ������Ʈ ��ǥ, ������Ʈ ũ��, ����
class Object
{
public:
	Coor			m_Coor;
	Vector3D		m_vDirection;
	Vector3D		m_vVelocity;
	Vector3D		m_vAcc;
	Vector3D		m_vForce;
	float		m_mMass;
	float		m_fFriction;
	float		m_fSpeed;
public:
	void SetPosition(Vector3D _ctPoint, Vector3D _size);
public:
	virtual void Frame(float _fDeltaTime, float fGameTime);
	virtual void AddForce(Vector3D _dir);
public:
	Object();
	~Object() {};
};

