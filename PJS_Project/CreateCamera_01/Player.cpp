#include "Player.h"

bool Player::Init()
{
	m_fSpeed = 100.0f;
	return true;
}
bool Player::Frame()
{
	Move();
	Fire();
	if (!m_pBulletList.empty())
	{
		std::list<Bullet*>::iterator iter;
		for (iter = m_pBulletList.begin(); iter!=m_pBulletList.end();iter++)
		{
			if (!(*iter)->Frame())
			{
				(*iter)->Release();
				delete (*iter);
				m_pBulletList.erase(iter);
				return true;
			}
		}
	}
	return true;
}

bool Player::Render()
{
	BObject::Render();
	for (auto iter : m_pBulletList)
	{
		iter->Render();
	}
	return true;
}

bool Player::Release()
{
	for (auto iter : m_pBulletList)
	{
		iter->Release();
		delete iter;
	}
	return true;
}

bool Player::Move()
{
	Vector2D _vPos = m_vPosition;
	if (I_Input.GetKey('W') == KEY_HOLD)
		_vPos.x += 1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
	if (I_Input.GetKey('S') == KEY_HOLD)
		_vPos.x += -1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
	SetPosition(_vPos);
	return true;
}

bool Player::Fire()
{
	m_fCurrTime += I_Timer.m_fDeltaTime;
	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		m_fChargingTime += I_Timer.m_fDeltaTime;
		m_fBulletPower = 20 *  (m_fChargingTime+1);
	}
	if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
	{
		if (m_fCurrTime > m_fFireCoolTime)
		{
			Bullet* _bullet = m_bFirePos.MakeBullet(m_p3dDevice, m_pImmediateContext, m_vCenterPoint);
			_bullet->m_fPower = m_fBulletPower;
			m_fCurrTime = 0;
			m_pBulletList.push_back(_bullet);
			m_fChargingTime = 0;
		}
	}
	return true;
}
