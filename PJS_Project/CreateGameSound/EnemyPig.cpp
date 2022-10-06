#include "EnemyPig.h"

bool EnemyPig::Init()
{
	//Sprite* newSprite = new Sprite;
	//m_pSprite = I_Sprite.GetPtr(L"MushIdle");
	SetAnim();
	//SetRect(rt);
	return true;
}

bool EnemyPig::Frame()
{
	SetCameraSize({ 800,600 });
	Update();
	//SetRect(m_rtInit);
	if (m_bEnemyDead)
	{
		SetAnimDead();
		m_bEnemyDead = false;
	}
	if (m_pSprite->m_szName == L"MushDead" && m_iIndex>=m_iMaxIndex)
	{
		this->Release();
		delete this;
		return false;
	}
	return true;
}

bool EnemyPig::SetAnim()
{
	m_pSprite = I_Sprite.GetPtr(L"MushIdle");
	Rect rt = m_pSprite->m_uvArray[0];
	m_iIndex = 0;
	m_iMaxIndex = m_pSprite->m_uvArray.size();
	m_fStep = 0.8f / m_iMaxIndex;
	SetRect(rt);
	//m_pSprite->SetRect(m_rtInit);
	//m_pSprite->SetPosition(m_vPosition, m_vCameraPos);
	return true;
}
bool EnemyPig::SetAnimDead()
{
	m_pSprite = I_Sprite.GetPtr(L"MushDead");
	Rect rt = m_pSprite->m_uvArray[0];
	m_iIndex = 0;
	m_iMaxIndex = m_pSprite->m_uvArray.size();
	m_fStep = 0.5f / m_iMaxIndex;
	SetRect(rt);
	
	return true;
}

bool EnemyPig::Update()
{
	m_fEffectTimer += I_Timer.m_fDeltaTime;
	if (m_fStep <= m_fEffectTimer)
	{
		m_fEffectTimer = 0;
		m_iIndex++;
	}
	if (m_iIndex >= m_iMaxIndex)
	{
		if (m_pSprite->m_szName == L"MushDead")
		{
			return false;
		}
		m_iIndex = 0;
		return false;
	}
	Rect rt = m_pSprite->m_uvArray[m_iIndex];
	m_rtInit = rt;
	return true;
}

bool EnemyPig::Render()
{
	//m_pSprite->SetPosition(m_vPosition, m_vCameraPos);
	SetRect(m_rtInit);
	SetPosition(m_vPosition, m_vCameraPos);
	Object2D::Render();
	return true;
}
