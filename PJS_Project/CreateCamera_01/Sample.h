#pragma once
#include "GameCore.h"
#include"Object2D.h"
#include "DxState.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>


class Player;

class Sample : public GameCore
{
public:
	BObject*		m_object;
	Player*			m_bPlayer;

public:

	//std::
public:
	bool Init() override;
	bool Frame() override;
	bool Render() override;
	bool Release() override;
public:
	bool DataLoad(const TCHAR* _fileLoad);
	bool SetPlayer();
	bool SetMapObject();
};

