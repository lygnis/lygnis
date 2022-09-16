#pragma once
#include "Object2D.h"
class Bullet;
class FirePos : public Object2D
{
public:
	bool Frame() override;
	bool Fire();
public:
	float m_fFireCoolTime = 2.0f;
	float m_fCurrTime;
	//Bullet* m_bBullet;
public:
	std::vector<Bullet*>	m_pBulletList;
};

