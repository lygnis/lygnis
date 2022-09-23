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
				AddEffect((*iter)->m_vFirePoint);
				(*iter)->Release();
				delete (*iter);
				m_pBulletList.erase(iter);
				m_bEffect = true;
				return true;
			}
		}
	}
	if (m_bEffect)
	{
		for (auto iter = m_pEffectList.begin();
			iter != m_pEffectList.end(); )
		{
			Efeect* pEffect = *iter;
			if (pEffect->Updata() == false)
			{
				delete pEffect;
				iter = m_pEffectList.erase(iter);
				continue;
			}
			iter++;
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
	for (auto pEffect : m_pEffectList)
	{
		pEffect->m_pSprite->SetRect(pEffect->m_tRect);
		pEffect->m_pSprite->SetPosition(pEffect->m_vPos);
		pEffect->m_pSprite->Render();
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
	for (auto iter : m_pEffectList)
	{
		delete iter;
	}
	m_pEffectList.clear();
	I_Sprite.Release();
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
			Bullet* _bullet = m_bFirePos.MakeBullet(m_p3dDevice, m_pImmediateContext, m_vPosition);
			_bullet->m_fPower = m_fBulletPower;
			m_fCurrTime = 0;
			m_pBulletList.push_back(_bullet);
			m_fChargingTime = 0;
		}
	}
	return true;
}

bool Player::AddEffect(Vector2D _pos)
{
	Efeect* pEffect = new Efeect;
	pEffect->m_pSprite = I_Sprite.GetPtr(L"rtExplosion");
	pEffect->m_fEffectTimer = 0.0f;
	Rect rt = pEffect->m_pSprite->m_uvArray[0];
	pEffect->m_tRect = rt;
	pEffect->m_iIndex = 0;
	pEffect->m_fLifeTime = 1.0f;
	pEffect->m_vPos = _pos;
	pEffect->m_fStep = pEffect->m_fLifeTime / pEffect->m_pSprite->m_uvArray.size();
	pEffect->m_iMaxIndex = pEffect->m_pSprite->m_uvArray.size();
	pEffect->m_pSprite->SetRect(pEffect->m_tRect);
	pEffect->m_pSprite->SetPosition(pEffect->m_vPos);
	pEffect->m_rtCollision = pEffect->m_pSprite->m_rtCollision;
	pEffect->m_rtCollision.x0 = pEffect->m_vPos.x;
	pEffect->m_rtCollision.y0 = pEffect->m_vPos.y;
	m_pEffectList.push_back(pEffect);
	return true;
}
