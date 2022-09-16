#include "FirePos.h"
#include "Bullet.h"
bool FirePos::Frame()
{
	Vector2D _vPos = m_vPosition;
	m_fSpeed = 100.0f;
	if (I_Input.GetKey('W') == KEY_HOLD)
		_vPos.x += 1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
	if (I_Input.GetKey('S') == KEY_HOLD)
		_vPos.x += -1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
	Fire();
	if (!m_pBulletList.empty())
	{
		for (int i = 0; i < m_pBulletList.size(); i++)
		{
			m_pBulletList[i]->Frame();
		}
	}
	SetPosition(_vPos);

	return true;
}

bool FirePos::Fire()
{
	m_fCurrTime += I_Timer.m_fDeltaTime;
	if (I_Input.GetKey(VK_LBUTTON) == KEY_PUSH)
	{
		if (m_fCurrTime > m_fFireCoolTime)
		{
			Bullet* bullet = new Bullet;
			bullet->SetDevice(m_p3dDevice, m_pImmediateContext);
			bullet->Create(L"D:/Git_PJS_C/PJS_Project/CreateObject/DefaultShader.txt", L"D:/Git_PJS_C/data/msadv_talltank.gif");
			bullet->SetRect({ 4,321,16,14 });
			bullet->SetPosition(m_vCenterPoint);
			bullet->GetMousePosition(I_Input.m_pMpos, m_vCenterPoint);
			m_pBulletList.push_back(bullet);
			m_fCurrTime = 0;
		}
	}
	return true;
}
