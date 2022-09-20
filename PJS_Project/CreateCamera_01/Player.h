#pragma once
#include "Object2D.h"
#include "FirePos.h"
#include "Bullet.h"
#include <list>
class Bullet;

class Player : public Object2D
{
public:
	FirePos					m_bFirePos;
	std::list<Bullet*>		m_pBulletList;
	float					m_fFireCoolTime = 0.1f;
	float					m_fCurrTime;
	float					m_fBulletPower = 0;
	float					m_fChargingTime = 0.0f;
public:
	bool Init();
	bool Frame() override;
	bool Render();
	bool Release();
public:
	bool Move();
	bool Fire();
};

