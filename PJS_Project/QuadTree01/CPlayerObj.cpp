#include "CPlayerObj.h"

void CPlayerObj::Frame(float fDeltaTime, float fGameTime)
{
	m_fSpeed = 10.0f;		// �ӷ�
	m_fMass = 100.0f;
	CVector vPos(m_rect.o_Px, m_rect.o_Py);			// ���� ����
	// ������ ������ ������
	// ������� = ���ۺ��� +���⺤�� * (�Ÿ� �Ǵ� �ð�), ������
	// ������ġ = ������ġ +���⺤�� * �ӷ�
	// ������ġ = ������ġ + �ӵ�
	// vPos = vPos + �ӵ�* �ð�(0.1f)
	// time = ���� ������ �ð� - ���� ������ �ð�
	// 1�ʿ� 10, 0, 0���� ��������.
	// 0.5f 5,0,0
	// 0.1f 1,0,0

	// V = V_0 +at;
	// ������ġ = ������ġ + v
	// �ӵ� -= t (max(0, �ӵ�)

	CVector _pos = m_vDirection * m_fSpeed * fDeltaTime;		// �ӵ��� ���� ���Ѵ� �ӷ� * ����
	AddForce(_pos);
	// ���ӵ��� ���Ѵ�.
	m_vAcc = m_vForce / m_fMass;
	// �ӵ��� ���Ѵ�
	CVector _velocity = m_vAcc * fDeltaTime;
	m_vVel += _velocity;							// v = v_0+at;
	vPos = vPos + m_vVel;							// ��� ���� = ���ۺ��� + ���⺤�� * speed* t( �Ÿ� ������ �ð�)
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
		vPos.x = 100.0f;					// ������Ʈ�� ��ǥ�� 100�� �Ѿ��
		m_vForce = CVector(0,0);			// ���� �ӵ��� 0���� �����
		m_vVel = CVector(0, 0);
		m_vDirection *= -1.0f;			// ������ �ݴ�� ����
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
	SetPosition(vPos.x, vPos.y, m_rect.w, m_rect.h);		// ������ ��ǥ�� ������ ����
}
