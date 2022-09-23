#pragma once
#include "FirePos.h"
#include "Bullet.h"
#include "Efeect.h"
#include <list>
class Bullet;

class Player : public Object2D
{
public:
	FirePos					m_bFirePos;
	float					m_fFireCoolTime = 0.1f;
	float					m_fCurrTime;
	float					m_fBulletPower = 0;
	float					m_fChargingTime = 0.0f;
	bool					m_bEffect = false;
public:
	std::list<Bullet*>		m_pBulletList;
	std::list<Efeect*>		m_pEffectList;
public:
	bool Init();
	bool Frame() override;
	bool Render();
	bool Release();
public:
	bool Move();
	bool Fire();
	bool AddEffect(Vector2D _pos);
};

