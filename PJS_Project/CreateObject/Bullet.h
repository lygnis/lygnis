#pragma once
#include "Object2D.h"
class Bullet : public Object2D
{
public:
	bool Frame()override;
	void GetMousePosition(POINT _vec, Vector2D _center);
};

