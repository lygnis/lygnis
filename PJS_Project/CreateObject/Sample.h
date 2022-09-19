#pragma once
#include "GameCore.h"
#include"Object2D.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

class Player;

class Sample : public GameCore
{
public:
	BObject*		m_object;
	Player*			m_bPlayer;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	bool SetPlayer();
	bool SetMapObject();
};

