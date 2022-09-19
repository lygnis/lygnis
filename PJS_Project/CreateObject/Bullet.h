#pragma once
#include "Object2D.h"
class Bullet : public Object2D
{
private:
	enum{GRVITY_AMOUNT = 50};
	Vector2D	m_vForce;
public:
	float		m_fPower = 10.0f;
	bool Frame()override;
	void GetMousePosition(POINT _vec, Vector2D _center);
public:
	Bullet();
};

