#pragma once
#include "Object2D.h"
class EnemyBalloon : public Object2D
{
public:
	bool MoveCheck = true;
	int	 m_iHp;
	int  m_iIndex;
	//Vector2D m_vStartpos;
public:
	bool Init();
	bool Frame() override;
	bool Render();
public:
	bool Move();
};

