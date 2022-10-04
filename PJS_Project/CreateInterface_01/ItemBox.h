#pragma once
#include "Object2D.h"
class ItemBox : public Object2D
{
public:
	int		m_iCountItem;
public:
	bool Init();
	bool Frame() override;
};

