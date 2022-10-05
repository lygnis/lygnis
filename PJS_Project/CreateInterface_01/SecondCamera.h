#pragma once
#include "Object2D.h"
#include "Interface.h"
class SecondCamera : public Object2D
{
	Interface* m_pInterface;
public:
	bool Init();
	bool Frame()override;
	bool Move();
	bool Render();
};

