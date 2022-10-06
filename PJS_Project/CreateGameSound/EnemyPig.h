#pragma once
#include "Object2D.h"
#include "SpriteManager.h"
class EnemyPig : public Object2D
{
public:
	int m_iScore;
	Sprite* m_pSprite = nullptr;
	int m_iIndex;
	float m_fStep;
	int m_iMaxIndex;
	float m_fEffectTimer;
	bool m_bEnemyDead = false;
public:
	//std::list<Sprite*> m_pSpriteList;
public:
	bool Init();
	bool Frame()override;
	bool SetAnim();
	bool SetAnimDead();
	bool Update();
	bool Render();
	bool UpdateDie();
};

