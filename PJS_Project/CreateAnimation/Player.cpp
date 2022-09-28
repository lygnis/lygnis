#include "Player.h"

bool Player::Init()
{
	m_fSpeed = 100.0f;
	m_vPosition = { g_rtClient.right / 2.0f, g_rtClient.bottom - 100.0f };
	TankMove();
	//TankIdle();
	return true;
}
bool Player::Frame()
{
	AnimState();
	Update();
	FireUpdate(m_bFire);
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
	//BObject::Render();
	m_pSprite->SetRect(m_rtInit);
	m_pSprite->SetPosition(m_vPosition);
	m_pSprite->Render();

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
	m_fIdleTime += I_Timer.m_fDeltaTime;
	if (m_fEnergy >= 0)
	{
		Vector2D _vPos = m_vPosition;
		if (I_Input.GetKey('W') == KEY_HOLD)
		{
			_vPos.x += 1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
			m_fEnergy -= I_Timer.m_fDeltaTime;
			m_iState = NONE;
			m_fIdleTime = 0;
		}
		if (I_Input.GetKey('S') == KEY_HOLD)
		{
			_vPos.x += -1.0f * m_fSpeed * I_Timer.m_fDeltaTime;
			m_fEnergy -= I_Timer.m_fDeltaTime;
			m_iState = NONE;
			m_fIdleTime = 0;
		}
		if (m_fIdleTime >= 3.0f)
		{
			m_iState = IDLE;
		}
		m_vPosition = _vPos;
		//SetPosition(_vPos);
	}
	else if (m_fEnergy <= 0 && m_iState !=FIRE)
	{
		m_iState = STAY;
	}
	return true;
}

bool Player::Fire()
{
	if (m_pBulletList.size() >= 1)
	{
		return true;
	}
	//m_fCurrTime += I_Timer.m_fDeltaTime;
	if (I_Input.GetKey(VK_LBUTTON) == KEY_HOLD)
	{
		m_fChargingTime += I_Timer.m_fDeltaTime;
		m_fBulletPower = 20 *  (m_fChargingTime+1);
		m_iState = FIRE;
		Rect rt = m_pSprite->m_uvArray[0];
		m_rtInit = rt;
		m_iIndex = 1;
		m_fIdleTime = 0;
	}
	if (I_Input.GetKey(VK_LBUTTON) == KEY_UP)
	{
		Bullet* _bullet = m_bFirePos.MakeBullet(m_p3dDevice, m_pImmediateContext, m_vPosition);
		_bullet->m_fPower = m_fBulletPower;
		m_fCurrTime = 0;
		m_pBulletList.push_back(_bullet);
		m_fChargingTime = 0;
		m_fIdleTime = 0;
		//m_iIndex = 1;
		m_bFire = true;
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

bool Player::Update()
{
	if (m_pSprite->m_szName != L"tankFire")
	{
		m_fEffectTimer += I_Timer.m_fDeltaTime;
		if (m_fStep <= m_fEffectTimer)
		{
			m_fEffectTimer = 0;
			m_iIndex++;
		}
		if (m_iIndex >= m_iMaxIndex)
		{
			m_iIndex = 0;
			return false;
		}
		Rect rt = m_pSprite->m_uvArray[m_iIndex];
		m_rtInit = rt;
		return true;
	}
}
bool Player::FireUpdate(bool _fire)
{
	if (_fire)
	{
		m_fEffectTimer += I_Timer.m_fDeltaTime;
		if (m_fStep <= m_fEffectTimer)
		{
			m_fEffectTimer = 0;
			m_iIndex++;
		}
		if (m_iIndex >= m_iMaxIndex)
		{
			m_bFire = false;
			m_iIndex = 0;
			if (m_fEnergy <= 0)
				m_iState = STAY;
			if (m_fEnergy > 0)
				m_iState = NONE;
			return false;
		}
		Rect rt = m_pSprite->m_uvArray[m_iIndex];
		m_rtInit = rt;
	}
}
void Player::AnimState()
{
	switch (m_iState)
	{
	case NONE:
		m_iState = TankMove();
		break;
	case IDLE:
		m_iState = TankIdle();
		break;
	case FIRE:
		m_iState = TankFire();
		break;
	case STAY:
		m_iState = TankStay();
		break;
	}
}

PlayerState Player::TankIdle()
{
	if (m_pSprite->m_szName != L"tankIdle")
	{
		m_pSprite = I_Sprite.GetPtr(L"tankIdle");
		Rect rt = m_pSprite->m_uvArray[0];
		m_iIndex = 0;
		m_iMaxIndex = m_pSprite->m_uvArray.size();
		m_fStep = 1.0f / m_iMaxIndex;
		SetRect(rt);
		m_pSprite->SetRect(m_rtInit);
		m_pSprite->SetPosition(m_vPosition);
	}
	return IDLE;
}

PlayerState Player::TankFire()
{
	if (m_pSprite->m_szName != L"tankFire")
	{
		m_pSprite = I_Sprite.GetPtr(L"tankFire");
		Rect rt = m_pSprite->m_uvArray[0];
		SetRect(rt);
		m_iIndex = 0;
		m_iMaxIndex = m_pSprite->m_uvArray.size();
		m_fStep = 1.0f / m_iMaxIndex;
		m_pSprite->SetRect(m_rtInit);
		m_pSprite->SetPosition(m_vPosition);
	}
	return FIRE;
}

PlayerState Player::TankStay()
{
	if (m_pSprite->m_szName != L"tankStay")
	{
		m_pSprite = I_Sprite.GetPtr(L"tankStay");
		Rect rt = m_pSprite->m_uvArray[0];
		m_iIndex = 0;
		m_iMaxIndex = m_pSprite->m_uvArray.size();
		m_fStep = 1.0f / m_iMaxIndex;
		SetRect(rt);
		m_pSprite->SetRect(m_rtInit);
		m_pSprite->SetPosition(m_vPosition);
	}
	return STAY;
}

PlayerState Player::TankLose()
{
	return PlayerState();
}

PlayerState Player::TankMove()
{
	m_pSprite = I_Sprite.GetPtr(L"tankMove");
	Rect rt = m_pSprite->m_uvArray[0];
	m_iIndex = 0;
	m_iMaxIndex = m_pSprite->m_uvArray.size();
	m_fStep = 1.0f / m_iMaxIndex;
	SetRect(rt);
	m_pSprite->SetRect(m_rtInit);
	m_pSprite->SetPosition(m_vPosition);
	return NONE;
}

