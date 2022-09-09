#pragma once
#include "CVector.h"
#include "CColision.h"
// ������Ʈ ����
// ������Ʈ�� ������ ������ �־� �ڽ����� ����� �� �ڽĿ��� �÷��̾�, ���� ���� ������Ʈ�� �����Ѵ�.
class CObject
{
public:
	CVector		m_vDirection;			// ����
	TRect		m_rect;				// rect
	Circle		m_Circle;
public:
	CVector		m_vAcc;				// ���ӵ�
	CVector		m_vVel;				// �ӵ�
	CVector		m_vForce;			// ��
	float		m_fFriction;			// ������
	float		m_fMass;				// ����
	float		m_fSpeed;			// 

public:
	void SetPosition(float x, float y, float w, float h);
	void SetCircle(float x, float y, float w, float h);

public:
	virtual void Frame(float fDeltaTime, float fGameTime);			// ����� �� ������
	virtual void AddForce(CVector _dir);
public:
	CObject();
	~CObject() {};
};

