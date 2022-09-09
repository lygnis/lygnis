#include "CDyanmicCharac.h"

void CDyanmicCharac::Frame(float fDeltaTime, float fGameTime)
{
	// ���� �ӷ°� ���Ը� �����Ѵ�.
	m_fSpeed = 10.0f;
	m_fMass = 100.0f;
	// ���� ���͸� �����.
	CVector _pos(m_rect.o_Px, m_rect.o_Py);
	CVector keyPos = m_vDirection * m_fSpeed * fDeltaTime;
	_pos = _pos + keyPos;

	m_fSpeed -= fDeltaTime;
	if (0 >= m_fSpeed)
	{
		m_fSpeed = rand() % 10;
	}
	if (_pos.x > 100.0f)
	{
		_pos.x = 100.0f;
		m_vDirection *= -1.0f;
	}
	if (_pos.x < 0.0f)
	{
		_pos.x = 0.0f;
		m_vDirection *= -1.0f;
	}
	if (_pos.y > 100.0f)
	{
		_pos.y = 100.0f;
		m_vDirection *= -1.0f;
	}
	if (_pos.y < 0)
	{
		_pos.y = 0.0f;
		m_vDirection *= -1.0f;
	}
	SetPosition(_pos.x, _pos.y, m_rect.w, m_rect.h);
}
