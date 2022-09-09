#include "CPlayerObj.h"

void CPlayerObj::Frame(float fDeltaTime, float fGameTime)
{
	m_fSpeed = 10.0f;		// 속력
	m_fMass = 100.0f;
	CVector vPos(m_rect.o_Px, m_rect.o_Py);			// 벡터 생성
	// 벡터의 직진의 방정식
	// 결과벡터 = 시작베터 +방향벡터 * (거리 또는 시간), 변위량
	// 최종위치 = 현재위치 +방향벡터 * 속력
	// 최종위치 = 현재위치 + 속도
	// vPos = vPos + 속도* 시간(0.1f)
	// time = 현재 프레임 시간 - 이전 프레임 시간
	// 1초에 10, 0, 0으로 움직이자.
	// 0.5f 5,0,0
	// 0.1f 1,0,0

	// V = V_0 +at;
	// 최종위치 = 현재위치 + v
	// 속도 -= t (max(0, 속도)

	CVector _pos = m_vDirection * m_fSpeed * fDeltaTime;		// 속도를 먼저 구한다 속력 * 방향
	AddForce(_pos);
	// 가속도를 구한다.
	m_vAcc = m_vForce / m_fMass;
	// 속도를 구한다
	CVector _velocity = m_vAcc * fDeltaTime;
	m_vVel += _velocity;							// v = v_0+at;
	vPos = vPos + m_vVel;							// 결과 벡터 = 시작벡터 + 방향벡터 * speed* t( 거리 내지는 시간)
	if (fabs(m_vForce.Length()) <= EPSILON && fabs(m_vVel.Length()) > EPSILON)
	{
		m_fFriction -= fDeltaTime;
		if (m_fFriction <= 0)
		{
			m_vVel = CVector(0, 0);
			m_fFriction = 1.0f;
		}
		m_vVel *= m_fFriction;
	}
	if (vPos.x > 100.0f)
	{
		vPos.x = 100.0f;					// 오브젝트의 좌표가 100을 넘어가면
		m_vForce = CVector(0,0);			// 힘과 속도를 0으로 맞춘다
		m_vVel = CVector(0, 0);
		m_vDirection *= -1.0f;			// 방향을 반대로 설정
	}
	if (vPos.x < 0.0f)
	{
		vPos.x = 0.0f;
		m_vForce = CVector(0, 0);
		m_vVel = CVector(0, 0);
		m_vDirection *= -1.0f;
	}
	if (vPos.y > 100.0f)
	{
		vPos.y = 100.0f;
		m_vForce= CVector(0, 0);
		m_vVel = CVector(0, 0);
		m_vDirection *= -1.0f;
	}
	if (vPos.y < 0.0f)
	{
		vPos.y = 0.0f;
		m_vForce = CVector(0, 0);
		m_vVel = CVector(0, 0);
		m_vDirection *= -1.0f;
	}
	m_vDirection.Nomalized();
	SetPosition(vPos.x, vPos.y, m_rect.w, m_rect.h);		// 움직인 좌표에 포지션 세팅
}
