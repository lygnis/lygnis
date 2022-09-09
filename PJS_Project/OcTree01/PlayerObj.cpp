#include "PlayerObj.h"

void PlayerObj::Frame(float _fDeltaTime, float fGameTime)
{
	m_fSpeed = 10.0f;
	m_mMass = 100.0f;
	Vector3D vPos(m_Coor.v_ctPoint.x, m_Coor.v_ctPoint.y, m_Coor.v_ctPoint.z);
	Vector3D vSize(m_Coor.v_Size);

	Vector3D	_pos = m_vDirection * m_fSpeed * _fDeltaTime;
	AddForce(_pos);
	m_vAcc = m_vForce / m_mMass;
	Vector3D _velocity = m_vAcc * _fDeltaTime;
	m_vVelocity = m_vVelocity+ _velocity;
	vPos = vPos + m_vVelocity;
	if (fabs(m_vForce.Length()) <= EPSILON && fabs(m_vVelocity.Length()) > EPSILON)
	{
		m_fFriction -= _fDeltaTime;
		if (m_fFriction <= 0)
		{
			m_vVelocity = Vector3D(0, 0, 0);
			m_fFriction = 1.0f;
		}
		m_vVelocity = m_vVelocity * m_fFriction;
	}
	if (vPos.x + m_Coor.v_Size.x > 100.0f)
	{
		vPos.x = 100 - m_Coor.v_Size.x;					// 오브젝트의 좌표가 100을 넘어가면
		m_vForce = Vector3D(0, 0,0);			// 힘과 속도를 0으로 맞춘다
		m_vVelocity = Vector3D(0,0, 0);
		m_vDirection = m_vDirection* -1.0f;			// 방향을 반대로 설정
	}
	if (vPos.x < 0.0f)
	{
		vPos.x = 0.0f;
		m_vForce = Vector3D(0,0, 0);
		m_vVelocity = Vector3D(0, 0,0);
		m_vDirection = m_vDirection* -1.0f;
	}
	if (vPos.y+ m_Coor.v_Size.y > 100.0f)
	{
		vPos.y = 100 - m_Coor.v_Size.y;
		m_vForce = Vector3D(0,0, 0);
		m_vVelocity = Vector3D(0,0, 0);
		m_vDirection = m_vDirection* -1.0f;
	}
	if (vPos.y < 0.0f)
	{
		vPos.y = 0.0f;
		m_vForce = Vector3D(0,0, 0);
		m_vVelocity = Vector3D(0,0, 0);
		m_vDirection = m_vDirection* -1.0f;
	}
	if (vPos.z + m_Coor.v_Size.z> 100.0f)
	{
		vPos.z = 100 - m_Coor.v_Size.z;
		m_vForce = Vector3D(0, 0, 0);
		m_vVelocity = Vector3D(0, 0, 0);
		m_vDirection = m_vDirection * -1.0f;
	}
	if (vPos.z < 0)
	{
		vPos.z = 0.0f;
		m_vForce = Vector3D(0, 0, 0);
		m_vVelocity = Vector3D(0, 0, 0);
		m_vDirection = m_vDirection * -1.0f;
	}
	m_vDirection.Nomalized();
	SetPosition(vPos, vSize);
}
