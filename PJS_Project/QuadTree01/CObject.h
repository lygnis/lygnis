#pragma once
#include "CVector.h"
#include "CColision.h"
// 오브젝트 설정
// 오브젝트에 물리적 설정을 넣어 자식한테 상속한 후 자식에서 플레이어, 동적 정적 오브젝트를 설정한다.
class CObject
{
public:
	CVector		m_vDirection;			// 방향
	TRect		m_rect;				// rect
	Circle		m_Circle;
public:
	CVector		m_vAcc;				// 가속도
	CVector		m_vVel;				// 속도
	CVector		m_vForce;			// 힘
	float		m_fFriction;			// 마찰력
	float		m_fMass;				// 질량
	float		m_fSpeed;			// 

public:
	void SetPosition(float x, float y, float w, float h);
	void SetCircle(float x, float y, float w, float h);

public:
	virtual void Frame(float fDeltaTime, float fGameTime);			// 상속한 후 재정의
	virtual void AddForce(CVector _dir);
public:
	CObject();
	~CObject() {};
};

