#pragma once
#include "TStd.h"
#include "Vector.h"
#include "SpriteManager.h"
class Efeect
{
public:
	Vector2D m_vPos;
	Vector2D m_vDir = { 0,1 };
	float m_fLifeTime = 1.33f;
	float m_fSpeed = 300.0f;
	UINT m_iIndex =0;
	UINT m_iMaxIndex = 1;
	float m_fEffectTimer = 0.0f;
	Rect m_tRect = { 0,0,0,0 };
	float m_fStep = 1.0f;
	Rect m_rtCollision;
	Sprite* m_pSprite = nullptr;
public:
	bool Updata();
};

