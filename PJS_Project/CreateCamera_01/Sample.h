#pragma once
#include "GameCore.h"
#include"Object2D.h"
#include "DxState.h"
#include <iostream>
#include "Efeect.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>


class Player;
class SpriteManager;

class Sample : public GameCore
{
public:
	BObject*		m_object;
	Player*			m_bPlayer;
public:
	std::list<Efeect*> m_pEffecList;
	float m_fCurrTime;
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	bool SetPlayer();
	bool SetMapObject();
	bool AddEffect();
};

